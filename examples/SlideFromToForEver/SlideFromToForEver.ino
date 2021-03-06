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
#include <Arduino.h>
#include "Grove_LCD_RGB_Backlight_Extension.hpp"

// set up the LCD's number of columns and rows
GroveLcdRgbBacklight rgbLcd(16, 2);
ColorSlider lcdSlider(Colors::Blue, Colors::Red);

void setup() {
	rgbLcd.initialize();
}

void loop() {

	rgbLcd.setCursor(0, 0);
	rgbLcd.print((float) millis() / 1000.0); // seconds since startup
	rgbLcd.print(" seconds");

	// wait 500 ms until we continue (above) with printing.
	// during the wait, we continue to "color-slide" every 10 ms.
	// 10 ms must not be specified here, it is the default (see method implementation).
	lcdSlider.delayAndSlide(rgbLcd, 500, 10);
}
