# Grove\_LCD\_RGB\_Backlight\_Extension
Extension for: Seeedstudio, Grove - LCD RGB Backlight

# License
License information can be found [here](./LICENSE.md).

# Development
For developent I use the Sloeber IDE (<https://eclipse.baeyens.it>).

# Required Libraries
This library requires:
- <https://github.com/pieterbl/Grove_LCD_RGB_Backlight>
  - which is a slightly modified version of <https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight>
  - none of the performed changes, modifies the original library behavior
  - some of the changes fix C++ compiler warnings
  - the other changes were style issues and some typos that were fixed
- Standard Arduino "Wire" library
  - \<Wire.h\> is required by "rgb\_lcd.cpp" from the Grove\_LCD\_RGB\_Backlight library

# The "Grove - LCD RGB Backlight" - Needs 5V

TEXT: TBD

PHOTO: TBD

# Provided Examples
| Example | Description |
| ------- | ----------- |
| [DebugSlider](./examples/DebugSlider.ino)               | Illustrates how to debug the ColorSlider on a "short" color range. |
| [DisplayTextRGB](./examples/DisplayTextRGB.ino)         | Illustrates how to set the RGB display color to red, to green, to blue, for-ever. |
| [SlideFromToForEver](./examples/SlideFromToForEver.ino) | Illustrates how to "slide" the RGB display color from blue to red, to blue to red, for-ever, while printing timer information. |
| [SlideRGB](./examples/SlideRGB.ino)                     | Illustrates how to "slide" the RGB display color from red to green, from green to blue, from blue to red, for-ever. |
| [SlideToBlue](./examples/SlideToBlue.ino)               | Illustrates how to "slide" the RGB display color from green to blue. |
