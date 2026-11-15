# Advanced Buffer Mode Readme

## Table of contents

* [Overview](#overview)
* [Enable](#enable)
* [Usage](#usage)
* [Rotation](#rotation)
* [Functions](#functions)
* [Memory use and bands](#memory-use-and-bands)
* [ESP32 notes](#esp32-notes)
* [Notes for driver authors](#notes-for-driver-authors)
* [Examples](#examples)

## Overview

**This mode is intended for high-RAM MCUs only.**

Advanced buffer mode keeps a copy of the entire display image, a screen buffer, in RAM and sends it to the display's VRAM in one pass.
This mode is off by default and should only be enabled when buffering offers a clear advantage. Use advanced buffer mode for complex rendering, animations, or special effects when your MCU
has enough free memory. For simpler projects or low-RAM devices, direct drawing may be more efficient.

**Benefits include:**

1. **Double buffering:** draw off-screen, then update the display in one flush to reduce flicker.
2. **Batch drawing:** perform multiple graphics operations before a single update for better efficiency.
3. **Special effects:** apply blending, fading, or custom image processing before pushing to the display.
4. **Performance gains:** memory writes are typically faster than direct display writes.

**Limitations:**

1. **High memory use:** requires enough free RAM to store the full display image.
2. **Flush overhead:**  transferring the buffer to the display takes time.
3. **Limited compatibility:** unsuitable for low-RAM devices.
4. Many normal-mode functions already use small local buffers internally,
   so the benefits may be minimal for simple graphics.

**Buffer size requirements:**

| Display size XxY | Bytes needed for frame buffer (XxYx2) | Bands (16 rows each) | Largest single allocation (bytes) |
| ------------ | ------------ | ------------ | ------------ |
| 96×64 | 12,288 | 4 | 3,072 |
| 128×128 | 32,768 | 8 | 4,096 |
| 240×240 | 115,200 | 15 | 7,680 |
| 240×320 | 153,600 | 20 | 7,680 |

Whether this mode will compile and work in a user's program depends on a combination of factors:
display resolution, the MCU type, its configuration,
and how much data memory remains after your program and other data structures are loaded.
Even MCUs with high total RAM may fail to run this mode if other parts of your code or libraries
reserve significant memory.

## Enable

To enable advanced buffer mode, you need to define the macro `dislib16_ADVANCED_SCREEN_BUFFER_ENABLE`.
This macro is located in the file `display16_common_LTSM.hpp` (USER OPTION 2).
By default, this macro is commented out or undefined.
Once enabled, the library will use the screen buffer for many drawing operations instead of
writing directly to the display VRAM.

## Usage

1. `setBuffer()` allocates the screen buffer to cover the entire screen, call it at the setup of
   display operations, after the display size and rotation have been set.
   The buffer starts zero-filled (black). Returns `DisLib16::Success`, or `DisLib16::MemoryAError`
   if the memory cannot be allocated or the display is too tall for the buffer
   (see [Memory use and bands](#memory-use-and-bands)).
   Calling it again releases the previous buffer first.
2. `destroyBuffer()` releases all of the buffer's memory, call it at the end of display operations.
3. `clearBuffer(colour)` fills the buffer with a colour. Returns `DisLib16::BufferEmpty`
   if no buffer is allocated.
4. `writeBuffer()` writes the whole buffer to the screen, band by band.
   By default each band is sent as a single SPI buffered write.
   There is also a row by row buffered write option, selected by passing a non-zero parameter,
   which certain displays require (for example the SSD1331).
   Returns `DisLib16::BufferEmpty` if no buffer is allocated.

With `dislib16_DEBUG_MODE_ENABLE` defined, `setBuffer()` prints the buffer size in bytes
and the number of bands to the serial port, and reports which band failed if an allocation fails.

## Rotation

The buffer is laid out for the display's width and height at the time `setBuffer()` is called.

1. Set the rotation **before** `setBuffer()`.(if non-default rotation used)
2. If the display's width and height differ, rotating changes that layout, so call `setBuffer()`
   **again after every rotation change**. It releases the old buffer and allocates a new one,
   zero-filled, so redraw the screen afterwards.
3. On square displays (for example 240×240) rotation does not change the layout
   and no re-allocation is needed.

Most programs set the rotation once at start-up and need no more than the typical setup at step 1.

## Functions

Once enabled the following functions will write to the screen buffer instead of
the VRAM of the display.

1. `drawPixel()`
2. All Bitmap functions.
3. All Draw text functions only IF **textCharPixelOrBuffer = true**

Note:

`fillRectBuffer` uses a local buffer in the function to write to display VRAM.
Note `fillRectBuffer` is wrapped by `fillScreen`.

## Memory use and bands

The screen buffer is split into horizontal bands of 16 rows. Each band is allocated separately
(width x 16 rows x 2 bytes, or 32 x width bytes), and the last band is shorter if the display
height is not a multiple of 16. The pixel data is stored as RGB565, high byte first.

Splitting the buffer matters on MCUs whose free memory is fragmented. Free RAM is not always
available as one big block: the largest contiguous free block can be much smaller than the total
free heap, and a single allocation the size of a full frame can fail even though plenty of memory
is free in total. With bands, the largest allocation needed is one band, for example 7,680 bytes
for a 240-pixel-wide display, and the total only has to be free in pieces.

The table of bands has room for 24 bands, so the tallest supported display is 384 rows
(24 x 16). `setBuffer()` returns `DisLib16::MemoryAError` for anything taller.
The limit is the constant `_maxBands` in `display16_graphics_LTSM.hpp`.

Heap use is slightly more than the raw buffer size, to allow for allocator overhead.

## ESP32 notes

An ESP32 without PSRAM is the clearest example of fragmented memory. Its free heap is spread over
several regions, and the largest contiguous block is much smaller than the total.
You can check both figures with:

```cpp
Serial.print("Free heap: ");
Serial.println(ESP.getFreeHeap());
Serial.print("Largest free block: ");
Serial.println(ESP.getMaxAllocHeap());
```

Measured on an ESP32-D0WDQ6 (revision v1.0, no PSRAM) running the `FRAME_BUFFER.ino` example
at 240×240 (115,200 bytes):

| | Free heap (bytes) | Largest free block (bytes) |
| ------------ | ------------ | ------------ |
| Before `setBuffer()` | 330,368 | 110,580 |
| After `setBuffer()` | 211,192 | 110,580 |

An earlier version of this mode allocated the buffer as one contiguous block.
At 240×240 that needs 115,200 bytes, more than the 110,580 byte largest free block above,
so the ESP32 aborted and rebooted in `setBuffer()` even though 330 KB of heap was free
(240×225, at 108,000 bytes, still fitted). The banded buffer allocates 15 bands of 7,680 bytes
instead, so it works.

These figures vary with the board, the Arduino core version and what else your program has already
allocated, so measure on your own setup. If `setBuffer()` returns `DisLib16::MemoryAError`,
free memory is too low or too fragmented for the display size: allocate the buffer early in
`setup()` before other large allocations, reduce the size of other allocations in your program,
or use a board with more RAM.

See github [issue 2 for more details.](https://github.com/gavinlyonsrepo/display16_LTSM/issues/2)

## Notes for driver authors

The storage behind the screen buffer is internal to the graphics library and its layout is
not part of the public API. A display driver that overrides `drawPixel()` must not access the
buffer directly. In buffer mode it should call the base class implementation instead, which
does the bounds check and writes the pixel to the buffer:

```cpp
void MyDriver::drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
#ifdef dislib16_ADVANCED_SCREEN_BUFFER_ENABLE
  display16_graphics_LTSM::drawPixel(x, y, color);
#else
  // device specific direct write to the display
#endif
}
```

The GC9D01 driver is an example, its double-pixel workaround is only needed for direct writes.

## Examples

There are examples downstream in driver libraries for Advanced buffer mode.
They are called "FRAME_BUFFER.ino".
