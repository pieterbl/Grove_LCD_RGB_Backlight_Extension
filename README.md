# Grove\_LCD\_RGB\_Backlight\_Extension
Extension for: Seeedstudio, Grove - LCD RGB Backlight

# License
License information can be found here <./LICENSE.md>.

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
