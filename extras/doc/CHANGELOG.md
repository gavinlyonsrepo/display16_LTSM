# Changelog Log for Display16_LTSM Library

* Version 1.0.0 August 2025 
  - Initial release of the Display16_LTSM library.
* Version 1.0.1 Jan 2026
  - Minor update
  - Updated drawFastHLine() & drawFastVLine() to draw to buffer
  when advanced buffer mode enabled :dislib16_ADVANCED_SCREEN_BUFFER_ENABLE.
* version 1.0.2 Feb 2026
  - Minor Update
  - Make drawPixel() and drawFastVLine() virtual so they can be defined in the 
  driver sub-class. This is needed to support GC9D01 display.
