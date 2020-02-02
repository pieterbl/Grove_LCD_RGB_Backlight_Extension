/*
 Copyright (c) 2020 Pieter Bloemendaal (https://github.com/pieterbl)

 Project Grove_LCD_RGB_Backlight_Extension
 (https://github.com/pieterbl/Grove_LCD_RGB_Backlight_Extension)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef __GROVE_LCD_RGB_BACKLIGHT_EXTENSION_HPP__
#define __GROVE_LCD_RGB_BACKLIGHT_EXTENSION_HPP__

#include <Arduino.h>

/*
 * Simple Color class.
 */
class Color {
private:
	unsigned char _red;
	unsigned char _green;
	unsigned char _blue;

public:
	inline Color(unsigned char r, unsigned char g, unsigned char b) :
			_red(r), _green(g), _blue(b) {
	}

	inline const String toString() const {
		String str = "{";

		str += "red(";
		str += _red;
		str += "),";

		str += "green(";
		str += _green;
		str += "),";

		str += "blue(";
		str += _blue;
		str += ")";

		str += "}";
		return str;
	}

	inline void set(unsigned char r, unsigned char g, unsigned char b) {
		_red = r;
		_green = g;
		_blue = b;
	}

	inline void increase(unsigned char r, unsigned char g, unsigned char b) {
		_red += r;
		_green += g;
		_blue += b;
	}

	inline void decrease(unsigned char r, unsigned char g, unsigned char b) {
		_red -= r;
		_green -= g;
		_blue -= b;
	}

	inline unsigned char red() const {
		return _red;
	}

	inline unsigned char green() const {
		return _green;
	}

	inline unsigned char blue() const {
		return _blue;
	}

};

/*
 * Colors class offers some predefined colors.
 */
class Colors {
public:
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Magenta;

private:
	Colors() {
	}

};

/*
 * By implementing class ColorSliderClient, your class can work together with the ColorSlider class.
 */
class ColorSliderClient {
public:
	ColorSliderClient() {
	}

	virtual ~ColorSliderClient() {
	}

	// convenience method
	int increaseAndSlideColor(unsigned char r, unsigned char g, unsigned char b,
			Color &color) {

		color.increase(r, g, b);
		slideColor(color);
		return 1;
	}

	// convenience method
	int decreaseAndSlideColor(unsigned char r, unsigned char g, unsigned char b,
			Color &color) {

		color.decrease(r, g, b);
		slideColor(color);
		return 1;
	}

	virtual void slideColor(const Color &color) = 0;
};

/*
 * Class ColorSlider allows you to easily "slide" the color of your LCD RGB Backlight,
 * from e.g. Blue to Red, or from Green to Blue.
 */
class ColorSlider {
private:
	// from which color to which color must we slide
	Color _from;
	Color _to;

	// keep some state
	Color _current; // current color
	int _direction = 1; // current direction: up == 1, down == -1

	bool _debugViaSerial = false;

public:
	ColorSlider(Color from, Color to) :
			_from(from), _to(to), _current(from) {
	}

	/*
	 * Wait for specified number of milliseconds.
	 * Do this in a loop. Slide a bit, wait a bit.
	 * The "wait a bit" is "msStepSize" long.
	 */
	void delayAndSlide(ColorSliderClient &client, unsigned long ms,
			unsigned long msStepSize = 5) {

		for (unsigned long i = 0; i < ms; i += msStepSize) {
			slide(client);
			delay(msStepSize);
		}

	}

	void slide(ColorSliderClient &client) {
		if (_direction == 1) {
			slideUp(client);
			return;
		}
		if (_direction == -1) {
			slideDown(client);
			return;
		}
	}

	inline void setDebugViaSerial(bool debugMe) {
		_debugViaSerial = debugMe;
	}

private:

	void debugViaSerial() {
		if (_debugViaSerial) {
			Serial.print("from:");
			Serial.print(_from.toString());
			Serial.print(" / ");
			Serial.print("current:");
			Serial.print(_current.toString());
			Serial.print(" / ");
			Serial.print("to:");
			Serial.print(_to.toString());
			Serial.println();
		}
	}

	inline void debugLineViaSerial(const String &str) {
		if (_debugViaSerial) {
			Serial.println(str);
		}
	}

	inline void reverseDirection() {
		_direction *= -1;
	}

	/*
	 * Going up, we slide: Red, Green, Blue.
	 */
	void slideUp(ColorSliderClient &client) {
		debugViaSerial();
		if (slideRed(client, _from, _to)) {
			return;
		}
		if (slideGreen(client, _from, _to)) {
			return;
		}
		if (slideBlue(client, _from, _to)) {
			return;
		}
		reverseDirection();
	}

	/*
	 * Going down, we slide: Blue, Green, Red.
	 */
	void slideDown(ColorSliderClient &client) {
		debugViaSerial();
		if (slideBlue(client, _to, _from)) {
			return;
		}
		if (slideGreen(client, _to, _from)) {
			return;
		}
		if (slideRed(client, _to, _from)) {
			return;
		}
		reverseDirection();
	}

	int slideRed(ColorSliderClient &client, Color &begin, Color &end) {
		if (begin.red() < end.red() && _current.red() < end.red()) {
			debugLineViaSerial("increase red");
			return client.increaseAndSlideColor(1, 0, 0, _current);
		}
		if (begin.red() > end.red() && _current.red() > end.red()) {
			debugLineViaSerial("decrease red");
			return client.decreaseAndSlideColor(1, 0, 0, _current);
		}
		// if equal => nothing to do
		debugLineViaSerial("red matches");
		return 0;
	}

	int slideGreen(ColorSliderClient &client, Color &begin, Color &end) {
		if (begin.green() < end.green() && _current.green() < end.green()) {
			debugLineViaSerial("increase green");
			return client.increaseAndSlideColor(0, 1, 0, _current);
		}
		if (begin.green() > end.green() && _current.green() > end.green()) {
			debugLineViaSerial("decrease green");
			return client.decreaseAndSlideColor(0, 1, 0, _current);
		}
		// if equal => nothing to do
		debugLineViaSerial("green matches");
		return 0;
	}

	int slideBlue(ColorSliderClient &client, Color &begin, Color &end) {
		if (begin.blue() < end.blue() && _current.blue() < end.blue()) {
			debugLineViaSerial("increase blue");
			return client.increaseAndSlideColor(0, 0, 1, _current);
		}
		if (begin.blue() > end.blue() && _current.blue() > end.blue()) {
			debugLineViaSerial("decrease blue");
			return client.decreaseAndSlideColor(0, 0, 1, _current);
		}
		// if equal => nothing to do
		debugLineViaSerial("blue matches");
		return 0;
	}

};

#endif
