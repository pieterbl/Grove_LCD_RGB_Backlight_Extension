/*
 MIT License

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
#include "rgb_lcd.h"

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
	static const Color Orange;
	static const Color ORANJE; // for all the Dutch folks out there ...
	static const Color Yellow;

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

	virtual void setBackgroundColor(const Color &color) = 0;

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

	// default color is Green
	ColorSlider() :
			_from(Colors::Green), _to(Colors::Green), _current(Colors::Green) {
	}

	// basically no sliding, all colors the same
	ColorSlider(const Color &init) :
			_from(init), _to(init), _current(init) {
	}

	// initialize for continuous sliding
	ColorSlider(const Color &from, const Color &to) :
			_from(from), _to(to), _current(from) {
	}

	/*
	 * Wait for specified number of milliseconds.
	 * Do this in a loop. Slide a bit, wait a bit.
	 * The "wait a bit" is "msStepSize" long.
	 */
	void delayAndSlide(ColorSliderClient &client, unsigned long ms,
			unsigned long msStepSize = 10) {

		// must set color here, otherwise in case of "to" and "from" color equal,
		// we will never "set" or "slide"
		client.setBackgroundColor(_current);

		for (unsigned long i = 0; i < ms; i += msStepSize) {
			slide(client);
			delay(msStepSize);
		}
	}

	/*
	 * slideFromTo, with delays of "msStepSize".
	 */
	void slideFromTo(ColorSliderClient &client, //
			const Color &from, const Color &to, //
			unsigned long msStepSize = 10) {

		initializeColors(from, to);

		// must set color here, otherwise in case of "to" and "from" color equal,
		// we will never "set" or "slide"
		client.setBackgroundColor(_current);

		while (slideUp(client) == 1) {
			delay(msStepSize);
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

	/*
	 * Going up, we slide: Red, Green, Blue.
	 */
	int slideUp(ColorSliderClient &client) {
		debugViaSerial();
		if (slideRed(client, _from, _to)) {
			return 1;
		}
		if (slideGreen(client, _from, _to)) {
			return 1;
		}
		if (slideBlue(client, _from, _to)) {
			return 1;
		}
		reverseDirection();
		return 0;
	}

	/*
	 * Going down, we slide: Blue, Green, Red.
	 */
	int slideDown(ColorSliderClient &client) {
		debugViaSerial();
		if (slideBlue(client, _to, _from)) {
			return 1;
		}
		if (slideGreen(client, _to, _from)) {
			return 1;
		}
		if (slideRed(client, _to, _from)) {
			return 1;
		}
		reverseDirection();
		return 0;
	}

	int slideRed(ColorSliderClient &client, //
			const Color &begin, const Color &end) {

		if (begin.red() < end.red() && _current.red() < end.red()) {
			debugLineViaSerial("increase red");
			return increaseAndSlideColor(client, _current, 1, 0, 0);
		}
		if (begin.red() > end.red() && _current.red() > end.red()) {
			debugLineViaSerial("decrease red");
			return decreaseAndSlideColor(client, _current, 1, 0, 0);
		}
		// if equal => nothing to do
		debugLineViaSerial("red matches");
		return 0;
	}

	int slideGreen(ColorSliderClient &client, //
			const Color &begin, const Color &end) {

		if (begin.green() < end.green() && _current.green() < end.green()) {
			debugLineViaSerial("increase green");
			return increaseAndSlideColor(client, _current, 0, 1, 0);
		}
		if (begin.green() > end.green() && _current.green() > end.green()) {
			debugLineViaSerial("decrease green");
			return decreaseAndSlideColor(client, _current, 0, 1, 0);
		}
		// if equal => nothing to do
		debugLineViaSerial("green matches");
		return 0;
	}

	int slideBlue(ColorSliderClient &client, //
			const Color &begin, const Color &end) {

		if (begin.blue() < end.blue() && _current.blue() < end.blue()) {
			debugLineViaSerial("increase blue");
			return increaseAndSlideColor(client, _current, 0, 0, 1);
		}
		if (begin.blue() > end.blue() && _current.blue() > end.blue()) {
			debugLineViaSerial("decrease blue");
			return decreaseAndSlideColor(client, _current, 0, 0, 1);
		}
		// if equal => nothing to do
		debugLineViaSerial("blue matches");
		return 0;
	}

	int increaseAndSlideColor(ColorSliderClient &client, Color &color, //
			unsigned char r, unsigned char g, unsigned char b) {
		color.increase(r, g, b);
		client.slideColor(color);
		return 1;
	}

	int decreaseAndSlideColor(ColorSliderClient &client, Color &color, //
			unsigned char r, unsigned char g, unsigned char b) {
		color.decrease(r, g, b);
		client.slideColor(color);
		return 1;
	}

	void initializeColors(const Color &from, const Color &to) {
		_from = from;
		_to = to;
		_current = from;
	}

};

class GroveLcdRgbBacklight: public rgb_lcd, public ColorSliderClient {
private:
	uint8_t _cols;
	uint8_t _lines;

public:

	GroveLcdRgbBacklight(uint8_t cols, uint8_t lines) :
			_cols(cols), _lines(lines) {
	}

	virtual ~GroveLcdRgbBacklight() {
	}

	void initialize() {
		rgb_lcd::begin(_cols, _lines);
	}

	virtual void setBackgroundColor(const Color &color) {
		rgb_lcd::setRGB(color.red(), color.green(), color.blue());
	}

	virtual void slideColor(const Color &color) {
		setBackgroundColor(color);
	}

	void setBackgroundColorRed() {
		setBackgroundColor(Colors::Red);
	}

	void setBackgroundColorGreen() {
		setBackgroundColor(Colors::Green);
	}

	void setBackgroundColorBlue() {
		setBackgroundColor(Colors::Blue);
	}

	void setBackgroundColorMagenta() {
		setBackgroundColor(Colors::Magenta);
	}

	void printAt(uint8_t col, uint8_t row, const String &str) {
		rgb_lcd::setCursor(col, row);
		rgb_lcd::print(str);
	}

	void printAt(uint8_t col, uint8_t row, const char *str) {
		rgb_lcd::setCursor(col, row);
		rgb_lcd::print(str);
	}

};

#endif
