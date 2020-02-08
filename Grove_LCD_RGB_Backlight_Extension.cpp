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
#include "Grove_LCD_RGB_Backlight_Extension.hpp"

const Color Colors::Black(0, 0, 0);
const Color Colors::White(255, 255, 255);

const Color Colors::Red(255, 0, 0);
const Color Colors::Green(0, 255, 0);
const Color Colors::Blue(0, 0, 255);

// https://rgbcolorcode.com/color/magenta
const Color Colors::Magenta(255, 0, 255);

// https://rgbcolorcode.com/color/orange
const Color Colors::Orange(255, 165, 0);
const Color Colors::ORANJE(255, 165, 0);

// https://rgbcolorcode.com/color/yellow
const Color Colors::Yellow(255, 255, 0);

// C++ compiler with Sloeber V4.3.2 complains that this pure virtual method
// must be implemented by class GroveLcdRgbBacklight. This is strange, since
// the write method is already implemented by class rgb_lcd.
inline size_t GroveLcdRgbBacklight::write(uint8_t value) {
	return rgb_lcd::write(value);
}

