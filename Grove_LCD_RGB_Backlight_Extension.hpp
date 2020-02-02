#ifndef __GROVE_LCD_RGB_BACKLIGHT_EXTENSION_HPP__
#define __GROVE_LCD_RGB_BACKLIGHT_EXTENSION_HPP__

#include <WString.h>

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

#endif
