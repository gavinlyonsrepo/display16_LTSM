/*!
	@file    display16_graphics_LTSM.hpp
	@author  Gavin Lyons
	@brief   header file for graphics class. 16-bit arduino display library. Display16_LTSM
*/

#pragma once

// Section: Includes
#include <display16_font_LTSM.hpp>
#include <SPI.h>
#include <math.h> // sin & cos


/*!
	@brief Class to handle graphics of ST7735 display
 */
class display16_graphics_LTSM : public display_Fonts , public Print
{

public:
	display16_graphics_LTSM ();
	~display16_graphics_LTSM (){
	#ifdef dislib16_ADVANCED_SCREEN_BUFFER_ENABLE
		freeBands();
	#endif
	};

	// Enums
	/*! @brief 16-bit color definitions (RGB565 format).*/
	enum  pixel_color565_e : uint16_t
	{
		C_BLACK   = 0x0000, /**< Black */
		C_BLUE    = 0x001F, /**< Blue */
		C_RED     = 0xF800, /**< Red */
		C_GREEN   = 0x07E0, /**< Green */
		C_CYAN    = 0x07FF, /**< Cyan */
		C_MAGENTA = 0xF81F, /**< Magenta */
		C_YELLOW  = 0xFFE0, /**< Yellow */
		C_WHITE   = 0xFFFF, /**< White */
		C_TAN     = 0xED01, /**< Tan */
		C_GREY    = 0x9CD1, /**< Grey */
		C_BROWN   = 0x6201, /**< Brown */
		C_DGREEN  = 0x01C0, /**< Dark Green */
		C_ORANGE  = 0xFC00, /**< Orange */
		C_NAVY    = 0x000F, /**< Navy */
		C_DCYAN   = 0x03EF, /**< Dark Cyan */
		C_MAROON  = 0x7800, /**< Maroon */
		C_PURPLE  = 0x780F, /**< Purple */
		C_OLIVE   = 0x7BE0, /**< Olive */
		C_LGREY   = 0xC618, /**< Light Grey */
		C_DGREY   = 0x7BEF, /**< Dark Grey */
		C_GYELLOW = 0xAFE5, /**< Greenish Yellow */
		C_PINK    = 0xFC18, /**< Pink */
		C_LBLUE   = 0x7E5F, /**< Light Blue */
		C_BEIGE   = 0xB5D2  /**< Beige */
	};
	/*! TFT rotate modes in degrees*/
	enum  display_rotate_e : uint8_t
	{
		Degrees_0 = 0, /**< No rotation 0 degrees*/
		Degrees_90,    /**< Rotation 90 degrees*/
		Degrees_180,   /**< Rotation 180 degrees*/
		Degrees_270    /**< Rotation 270 degrees*/
	};

public:
	// === buffer screen mode functions ===
#ifdef dislib16_ADVANCED_SCREEN_BUFFER_ENABLE
	DisLib16::Ret_Codes_e setBuffer(void);
	DisLib16::Ret_Codes_e clearBuffer(uint16_t color = C_BLACK);
	DisLib16::Ret_Codes_e writeBuffer(uint8_t bufferMode = 0);
	DisLib16::Ret_Codes_e destroyBuffer(void);
	void freeBands(void); /**< Silent release of all bands */
#endif 
	// ====================================
	// Screen functions
	/*! @brief define in the sub class */
	virtual void setAddrWindow(uint16_t, uint16_t, uint16_t, uint16_t) = 0;
	void fillScreen(uint16_t color);
	void setCursor(int16_t x, int16_t y);
	virtual void drawPixel(uint16_t, uint16_t, uint16_t);
	// Graphics functions
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	virtual void drawFastVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color);
	void drawFastHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color);
	void drawRectWH(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
	DisLib16::Ret_Codes_e fillRectBuffer(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
	void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
	void drawRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);
	void fillRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);
	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
// Advanced graphics functions
#ifdef dislib16_ADVANCED_GRAPHICS_ENABLE
	void drawEllipse(int16_t cx, int16_t cy, int16_t semiMajorAxis, int16_t semiMinorAxis, bool fill, uint16_t color);
	DisLib16::Ret_Codes_e drawDotGrid(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t DotGridGap, uint16_t color);
	void drawQuadrilateral(int16_t x0, int16_t y0,int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color);
	void fillQuadrilateral(int16_t x0, int16_t y0,int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color);
	DisLib16::Ret_Codes_e  drawPolygon(int16_t x, int16_t y, uint8_t sides, int16_t diameter, float rotation, bool fill , uint16_t color);
	void drawLineAngle(int16_t x, int16_t y, int angle, uint8_t start, uint8_t length, int offset, uint16_t color);
	void drawArc(uint16_t cx, uint16_t cy, uint16_t radius, uint16_t thickness, float startAngle, float endAngle, uint16_t color);
	float getArcAngleMax() const;
	void setArcAngleMax(float arcAngleMax);
	int getArcAngleOffset() const;
	void setArcAngleOffset(int arcAngleOffset);
#endif
	// Text functions
	virtual size_t write(uint8_t) override;
	void setTextWrap(bool w);
	void setTextColor(uint16_t c);
	void setTextColor(uint16_t c, uint16_t bg);
	DisLib16::Ret_Codes_e  writeChar( uint16_t x, uint16_t y, char value );
	DisLib16::Ret_Codes_e  writeCharString( uint16_t x, uint16_t y, char *text);
	void setTextCharPixelOrBuffer(bool mode);
	bool getTextCharPixelOrBuffer() const;
	// Bitmap functions
	DisLib16::Ret_Codes_e drawBitmap(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t col, uint16_t bgcol, const uint8_t* data);
	DisLib16::Ret_Codes_e drawBitmap8Data(uint16_t x, uint16_t y, const uint8_t* data, uint16_t w, uint16_t h);
	DisLib16::Ret_Codes_e drawBitmap16Data(uint16_t x, uint16_t y, const uint8_t* data, uint16_t w, uint16_t h);
	DisLib16::Ret_Codes_e drawSpriteData(uint16_t x, uint16_t y, const uint8_t* data, uint16_t w, uint16_t h, uint16_t bgColor, bool printBg);

protected:
	// SPI function
	void spiStartTransaction(void);
	void spiEndTransaction(void);
	void writeCommand(uint8_t);
	void writeData(uint8_t);
	void spiWrite(uint8_t);
	void spiWriteSoftware(uint8_t spidata);
	void spiWriteDataBuffer(uint8_t *spidata, uint32_t len);

protected:
	// SPI variables
	bool _hardwareSPI;			  /**< True for Hardware SPI on , false for Software SPI on*/
	uint32_t _speedSPIHz;		  /**< SPI speed value in hertz*/
	uint16_t _SWSPIGPIODelay = 0; /**< uS GPIO Communications delay, SW SPI ONLY */
	// text variables
	bool _textwrap = true;			/**< wrap text around the screen on overflow*/
	uint16_t _textcolor = 0xFFFF;	/**< ForeGround color for text*/
	uint16_t _textbgcolor = 0x0000; /**< BackGround color for text*/
	// Screen variables
	int16_t _cursorX = 0; /**< Current pixel column postion of Cursor*/
	int16_t _cursorY = 0; /**< Current pixel row position of Cursor*/
	uint8_t _XStart;      /**< Records column offset postion */
	uint8_t _YStart;      /**< Records row offset postion */
	uint16_t _width;      /**< Records width TFT postion */
	uint16_t _height;     /**< Records Height TFT postion */
	// GPIO variables
	int8_t _display_DC;	   /**< GPIO Data or command line */
	int8_t _display_RST;   /**< GPIO Reset line */
	int8_t _display_CS;	   /**< GPIO Chip select line */
	int8_t _display_SCLK;  /**< GPIO Clock SPI Line */
	int8_t _display_SDATA; /**< GPIO MOSI data into display SPI Line */
	int8_t _display_MISO; /**< GPIO  MISO data out SPI Line */
#ifdef dislib16_ADVANCED_SCREEN_BUFFER_ENABLE
	static constexpr uint8_t  _bandShift = 4;                 /**< log2 of rows per band , user can adjust */
	static constexpr uint16_t _bandRows  = 1u << _bandShift;  /**< Rows per band (16)*/
	static constexpr uint8_t  _maxBands  = 24;                /**< 24 x 16 = 384 rows max, user can adjust */
	uint8_t* _screenBands[_maxBands] = {nullptr};             /**< the table of pointers, 
																each to a separately allocated block holding one band’s rows 
																(_bandRows × _width × 2 bytes)One calloc'd block per band */
	uint8_t  _bandCount = 0;                                  /**< Bands currently allocated, Zero means “no buffer”, */
	uint16_t _bufWidth  = 0; /**< Display width the bands were allocated for */
	uint16_t _bufHeight = 0; /**< Display height the bands were allocated for */	
	/*!
		@brief Number of pixel rows held by one band of the screen buffer.
		@param band Zero-based band index. Must be less than the number of
			bands in use, i.e. ceil(_height / _bandRows).
		@return _bandRows (16) for every band except possibly the last.
			When the display height is not a multiple of _bandRows the last
			band holds the remaining rows, e.g. height 230 gives bands 0-13
			with 16 rows and band 14 with 6.
		@note Used by setBuffer() to size each band's allocation, and by
			clearBuffer() and writeBuffer() to bound their loops.
			The band index is not range checked.
	*/
	inline uint16_t bandRowCount(uint16_t band) const
	{
		uint16_t left = _height - (band << _bandShift);
		return (left < _bandRows) ? left : _bandRows;
	}
#endif

private:
	// Helper functions graphics 
	inline void swapint16t(int16_t& a, int16_t& b)
	{
		int16_t t = a;
		a = b;
		b = t;
	}
	uint16_t convert8bitTo16bit(uint8_t RRRGGGBB);
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
#ifdef dislib16_ADVANCED_GRAPHICS_ENABLE
	void ellipseHelper(uint16_t cx, uint16_t cy, uint16_t x, uint16_t y, uint16_t color);
	void drawArcHelper(uint16_t cx, uint16_t cy, uint16_t radius, uint16_t thickness, float start, float end, uint16_t color);
	float sineFromDegrees(float angle);
	float cosineFromDegrees(float angle);

	float _myPI = 3.14159265358979323846f; /**< Pi constant */
	float _arcAngleMax = 360.0f; /**< Maximum angle of Arc , used by drawArc*/
	int _arcAngleOffset= 0; /**< used by drawArc, offset for adjusting the starting angle of arc. default positive X-axis (0°)*/
#endif

	bool _textCharPixelOrBuffer = false;  /**< Text character is drawn by local function buffer(false) or pixel(true) */
};


// ********************** EOF *********************
