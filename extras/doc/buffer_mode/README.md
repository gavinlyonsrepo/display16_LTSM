# Advanced Buffer Mode Readme

## Table of contents

* [Overview](#overview)  
* [Enable](#enable)  
* [Usage](#usage)  
* [Functions](#functions)  
* [Examples](#examples)

## Overview

**This mode is intended for high-RAM MCUs only.**

Advanced buffer mode uses a global screen buffer (`screenBuffer`) to store the entire display 
image in memory before sending it to the display’s VRAM. 
This mode is off by default and should only be enabled when buffering offers a clear advantage.
The buffer is stored in a `std::vector`.

**Benefits include:**
- **Double buffering:** draw off-screen, then update the display in one flush to reduce flicker.
- **Batch drawing:** perform multiple graphics operations before a single update for better efficiency.
- **Special effects:** apply blending, fading, or custom image processing before pushing to the display.
- **Performance gains:** memory writes are typically faster than direct display writes.

**Limitations:**
- **High memory use:** requires enough heap to store the full display image.
- **Flush overhead:** transferring the buffer to the display takes time.
- **Limited compatibility:** unsuitable for low-RAM devices.
- Many normal-mode functions already use small local buffers internally, so the benefits may be minimal for simple graphics.

Use advanced buffer mode for complex rendering, animations, or special effects when your MCU has enough free memory. For simpler projects or low-RAM devices, direct drawing may be more efficient.

**Buffer size requirements:**

| Display size XxY | Bytes needed for frame buffer (XxYx2) |
| ------------ | ------------ |
| 96×64         | 12,288  |
| 128×128       | 32,768   |
| 240×320       | 153,600 |

Whether this mode will compile and work in a users program depends on a combination factors 
: display resolution, the MCU type, its configuration, 
and how much data memory remains after your program and other data structures are loaded. 
Even MCUs with high total RAM may fail to run this mode if other parts of your code or libraries 
reserve significant memory. Support for 'std::vector' is also required by MCU compiler.


## Enable

To enable advanced buffer mode, you need to define the macro `dislib16_ADVANCED_SCREEN_BUFFER_ENABLE`. 
This macro is located in the file `display16_common_LTSM.hpp` (USER OPTION 2). 
By default, this macro is commented out or undefined. 
Once enabled, the library will use the `screenBuffer` for many drawing operations instead of 
writing directly to the display VRAM.

## Usage

1. setBuffer, sets the buffer allocates memory for a buffer to cover entire screen, call at setup of Display operations.
2. destroyBuffer, destroys buffer de-allocates memory, call at end of Display operations.
3. clearBuffer, fills buffer with a colour, by default black.
4. writeBuffer, writes buffer in a single SPI buffered write to screen.
By default this will use a single write but there is also a row by row
buffered write option, if passed parameter, certain displays require this option.

## Functions

Once enabled The following functions will write to screen Buffer instead of 
VRAM of display.

1. drawPixel()
2. All Bitmap functions.
3. All Draw text functions only IF **textCharPixelOrBuffer = true** 

Note:

FillRectBuffer uses a local buffer in function to write to display VRAM.
Note fillRectBuffer is wrapped by fillScreen. 

## Examples

There are examples downstream in driver libraries for Advanced buffer mode. There are called "FRAME BUFFER.ino".
