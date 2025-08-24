# Fonts Readme

## Table of contents

* [Overview](#overview)  
* [Drawing method](#drawing-method)  
* [Font data table](#font-data-table)  
* [Adding a font](#adding-a-font)  
* [Sources](#sources)  
* [Font Images](#font-images)

## Overview

There are 16 fonts packaged with library. Fonts can be added or removed by user.
All the Font data is in folder 'fonts_LTSM' but user can store custom fonts where they want.
Wanted fonts are included in the ino file. Unwanted fonts are not included and do not
count towards memory usage. Fonts are stored in Program memory.

## Drawing method

There are two methods for drawing text.
The character frame buffer method is default and is five times faster, the disadvantage being it 
uses some temporary dynamic memory to hold character buffer, Which could become an issue
on low RAM MCU using large fonts. The buffer created is size :  Font_X_Size * Font_Y_Size * 2.
Adjust which method is used using setTextCharPixelOrBuffer() function.
If using 'Advanced Frame buffer mode' (USER OPTION 2) use method 1 (Draw by pixel by pixel).

| num | method  | textCharPixelOrBuffer | Default| 
| ------ | ------ | ------ |  ------ | 
| 1 | Draw by pixel by pixel | true |  No | 
| 2 | Character frame buffer | false |  Yes | 


## Font data table 

| num | Font name | character size XxY|  ASCII range | Size in bytes |
| ------ | ------ | ------ | ------ |  ------ |
| 1 | FontDefault | 8x8 |  020-0x7E| 764 |
| 2 | FontSinclairS  | 8x8 | 0x20-0x7E | 764 |
| 3 | FontGll | 8x8 | 0x20-0x5A , NO lowercase letters | 476 |
| 4 | FontPico | 8x12 | 0x20-0x7E  | 1144|
| 5 | FontRetro | 8x16 | 0x20-0x7E | 1524 |
| 6 | FontMega | 16x16 | 0x20-0x7E | 3044 |
| 7 | FontArialBold  | 16x16 | 0x20 0x7E |  3044 |
| 8 | FontHallfetica | 16x16 | 0x20-0x7E | 3044 |
| 9 | FontOrla | 16x24 | 0x20-0x7E | 4564 |
| 10 | FontArialRound| 16x24 | 0x20-0x7E | 4564 |
| 11 | FontGroTesk | 16x32 | 0x20-0x7A |  5828 |
| 12 | FontInconsola | 24x32 | 0x20-0x7A | 8740 |
| 13 | FontMint | 24x32  | 0x20 -0x7A |  8740 |N |
| 14 | FontSixteenSeg | 32x48 | 0x2D-0x3A , 0-10 : . / - only |2692 |
| 15 | FontSevenSeg | 32X50| 0x2D-0x3A , 0-10 : . / - only | 2804 |
| 16 | FontGroTeskBig | 32X64| 0x20 - 0x5A, NO lowercase letters | 15108 |


Font size in bytes = ((X * (Y/8)) * numberOfCharacters) + (ControlBytes)

| Font class Function | Notes |
| ------ | ------ | 
| writeChar| draws single character |
| writeCharString | draws character array|
| print | Polymorphic print class which will print out many data types , arduino print-in|

## Adding a font

User can create their own fonts.
Make a .hpp file for your font.
A new ASCII font must have following font structure.
First 4 bytes are control bytes followed by **horizontally** addressed font data.
Also the fonts character width (or x-size) must be divisible evenly by 8.

```
// Example Font
// An 8 by 8 character size font starting at 
// ASCII offset 0x30 in ASCII table with 0x02 characters in font. 
// 0 and 1 , size 20 bytes, 4 Control bytes at start.
static const uint8_t FontBinaryExample[20] FLASH_STORAGE   =
{
0x08, 0x08, 0x30, 0x01,   // x-size, y-size, offset, (last character-offset : 0x31-0x30)
0x7C,0xC6,0xCE,0xD6,0xE6,0xC6,0x7C,0x00, // ASCII font data '0' : 0x30
0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0x00 // ASCII font data  '1' : 0x31
};
```

Then just include the font file in your .ino program.

## Sources

Fonts can be made from **ttf** files using [this tool.](https://github.com/gavinlyonsrepo/Colossus_LTSM) also written by author. 

Some of the fonts packaged with library came from [rinky dink electronics ](http://rinkydinkelectronics.com/)

## Font Images

Default 

[![Font Image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/default.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/default.png)

Pico

[![Font Image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/pico.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/pico.png)

SinclairS

[![Font Image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/sinclair.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/sinclair.png)

Retro 

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/retro.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/retro.png)

Arial Bold

[![Font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/arialbold.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/arialbold.png)

Hallfetica

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/hall.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/hall.png)


Arial Round

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/arialround.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/arialround.png)

Orla 

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/orla.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/orla.png)

GroTesk

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/grotesk.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/grotesk.png)

Inconsola

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/inconsola.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/inconsola.png)

Mint

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/mint.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/mint.png)

Sixteen Segment 

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/ss.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/ss.png)

Seven  Segment 

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/7seg.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/7seg.png)

GroTesk Big

[![font image](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/groteskbig.png)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/fonts/groteskbig.png)
