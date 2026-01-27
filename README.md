[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

# display16_LTSM Readme

## Table of contents

  * [Overview](#overview)
  * [Installation](#installation)
  * [Supported devices](#supported-devices)
  * [Software](#software)
    * [API documentation](#api-documentation)
    * [Fonts](#fonts)
    * [Bitmaps](#bitmaps)
    * [Advanced Graphics](#advanced-graphics)
    * [Advanced buffer mode](#Advanced-buffer-mode)
    * [Debug mode](#debug-mode)
    * [File-system](#file-system)
    * [Error Codes](#error-codes)
  * [Notes](#notes)

## Overview

* Name : display16_LTSM
* Title : Graphics Library for 16-bit color graphic displays for Arduino eco-system.
* Description :

0. C++ Library to support 16-bit color graphic displays.
1. Graphics class included.
2. Bitmaps supported: 1, 8, and 16 bit + sprites.
3. Multiple displays supported, see supported-devices below, new components can be added.
    Device display driver are separate libraries that import this one.
    User can write their own if device not supported.
4. 16 fonts included, new fonts can be easily added without changing source code
5. [URL project github link](https://github.com/gavinlyonsrepo/display16_LTSM)

* Author: Gavin Lyons


## Installation

The library is included in the official Arduino library manger and the optimum way to install it is using the library manager which can be opened by the *manage libraries* option in Arduino IDE. 

## Supported devices

Component drivers are separate dependent downstream libraries that include this library.

| Component name | Type | Interface | Readme URL link |
| -------- | ---------- | --------- | ---------- |
| ST7735 | TFT LCD|SPI HW & SW| [github link](https://github.com/gavinlyonsrepo/ST7735_LTSM)|
| ST7789 | TFT LCD|SPI HW & SW| [github link](https://github.com/gavinlyonsrepo/ST7789_LTSM)|
| SSD1331| OLED |SPI HW & SW  | [github link](https://github.com/gavinlyonsrepo/SSD1331_LTSM)|
| ILI9341 | TFT LCD |SPI HW & SW  | [github link](https://github.com/gavinlyonsrepo/ILI9341_LTSM)|
| GC9A01 | TFT LCD |SPI HW & SW  | [github link](https://github.com/gavinlyonsrepo/GC9A01_LTSM)|
| GC9D01 | TFT LCD |SPI HW & SW  | [github link](https://github.com/gavinlyonsrepo/GC9D01_LTSM)|

## Software

### API Documentation

Code is commented for doxygen API documentation software.

### Fonts

The font system readme is in the 'doc' folder [at link.](extras/doc/fonts/README.md)

### Bitmaps

Functions to support drawing bitmaps & sprites.

| Num | Function Name | Colour support | bitmap size max (128X128 screen) |  Note |
| ------ | ------ | ------ | ------ | ------ |
| 1 | drawBitmap | bi-colour | 2048 bytes  | Data horizontally addressed |
| 2 | drawBitmap8Data | 8 bit color RRRGGGBB  | 16384  | Data from array, Converted by software to 16-bit color |
| 3 | drawBitmap16Data | 16 bit color 565  | 32768  | Data from array |
| 4 | drawSpriteData  | 16 bit color  565 | 32768  | Data from array , Draws background color transparent | 

1. Bitmap size in kiloBytes = (screenWidth * screenHeight * bitsPerPixel)/(1024 * 8)
2. The data array for 1 is created from image files using file data conversion tool [link](https://javl.github.io/image2cpp/)
3. The data array for 2-4  is created from BMP files using file data conversion tool [link](https://notisrac.github.io/FileToCArray/)
4. 8-bit bitmaps only take half the memory of 16-bit bitmaps, at the expense of color depth:
   256 colors vs 65,536 colors.


### Advanced Graphics Mode

It is **OFF** by default.
There is an advanced graphics modes in library.
Standard graphics supports drawing lines, pixels
rectangles, triangles, circles and rounded rectangles.
Advanced graphics supports drawing polygons, dot grid, quadrilaterals, 
arcs, ellipses and lines at an angle.
If you want these 'advanced' functions, simply 
comment in define dislib16 ADVANCED GRAPHICS ENABLE in display16 common LTSM.hpp. 
This will enable advanced graphics mode. If this is disabled some examples 
may not work fully or even compile.

### Advanced buffer mode

It is **OFF** by default.
Advanced buffer mode. There is advanced buffer mode where the code writes 
to a global screen buffer instead of the VRAM of display. More details at readme, 
which is in the 'doc' folder [at link.](extras/doc/buffer_mode/README.md)
**This mode is only for high RAM MCUs.**

### Debug Mode 

This is **OFF** by default
If debug mode is enabled: error messages, warnings & important information is sent to serial monitor.
User ino file must enable serial port. To enable simply 
comment in define dislib16 DEBUG MODE ENABLE in file display16 common LTSM.hpp.


### File system

File system Hierarchy:

[![ pic ](https://github.com/gavinlyonsrepo/display16_LTSM/blob/main/extras/images/filesystem.jpg)](https://github.com/gavinlyonsrepo/display16_LTSM/blob/main/extras/images/filesystem.jpg) 

### Error Codes

Most functions that return a value, return a enum.
Zero for success and a positive number for an error code.
The enum is in file: display16 common LTSM.hpp.

## Notes
