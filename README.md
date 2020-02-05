# Grove\_LCD\_RGB\_Backlight\_Extension

Extension for: Seeedstudio, Grove - LCD RGB Backlight

## License

License information can be found [here](./LICENSE.md).

## Development

- For Arduino/C++ development **Sloeber** was used (<https://eclipse.baeyens.it>).
- For Markdown editing Visual Studio Code was used, with following plug-ins for:
  - Language checking: **Code Spell Checker**
  - Style checking: **Markdown All in One**, and **markdownlint**

## Hardware

Following hardware was used for this project:

- [Arduino UNO R3](https://www.seeedstudio.com/Arduino-Uno-Rev3-p-2995.html) (my board says UNO R3, from arduino.org)
- [Grove Base Shield V2.0 for Arduino](http://wiki.seeedstudio.com/Base_Shield_V2/) (using version 2.1)
  - see also: <https://www.seeedstudio.com/Base-Shield-V2.html>
- [Grove - LCD RGB Backlight](http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/) (using version 4.0)
  - see also: <https://www.seeedstudio.com/Grove-LCD-RGB-Backlight.html>

## Required Libraries

This library requires:

- <https://github.com/pieterbl/Grove_LCD_RGB_Backlight>
  - which is a slightly modified version of <https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight>
  - none of the performed changes, modifies the original library behavior
  - some of the changes fix C++ compiler warnings
  - the other changes were style issues and some typos that were fixed
- Standard Arduino "Wire" library
  - \<Wire.h\> is required by "rgb\_lcd.cpp" from the Grove\_LCD\_RGB\_Backlight library

## The "Grove - LCD RGB Backlight" - Needs 5V

See [Grove Base Shield V2.0 for Arduino](https://www.seeedstudio.com/Base-Shield-V2.html) documentation, stating:

- Every Grove connector has four wires, one of which is the VCC. However, not every micro-controller main board needs a supply voltage of 5V, some boards only need 3.3V.
- That's why we add a power toggle switch to Base Shield V2 so that you can select the suitable voltage of the micro-controller main board you are using via this switch.
- For example, **if you are using Arduino UNO with Base Shield V2, please turn the switch to 5V position;** while using Seeeduino Arch with Base Shield V2, please turn the switch to 3.3V.

## Provided Examples

| Example | Description |
| ------- | ----------- |
| [DebugSlider](./examples/DebugSlider/DebugSlider.ino)                      | Illustrates how to debug the ColorSlider on a "short" color range. |
| [DisplayTextRGB](./examples/DisplayTextRGB/DisplayTextRGB.ino)             | Illustrates how to set the RGB display color to red, to green, to blue, for-ever. |
| [SlideFromToForEver](./examples/SlideFromToForEver/SlideFromToForEver.ino) | Illustrates how to "slide" the RGB display color from blue to red, to blue to red, for-ever, while printing timer information. |
| [SlideRGB](./examples/SlideRGB/SlideRGB.ino)                               | Illustrates how to "slide" the RGB display color from red to green, from green to blue, from blue to red, for-ever. |
| [SlideToBlue](./examples/SlideToBlue/SlideToBlue.ino)                      | Illustrates how to "slide" the RGB display color from green to blue. |
