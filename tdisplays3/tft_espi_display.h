#include <sstream>              // istringstream, ostringstream
#include <iomanip>              // time functions
#include <SPI.h>
#include <TFT_eSPI.h>
#include "esphome.h"
#include "OpenFontRender.h"

#ifndef DISPLAYCONTROLLER
#define DISPLAYCONTROLLER

// wrapper class for talking to the display on the T-Display-S3
// use the spr object and spr.pushSprite to get double buffering to get double buffering
class DisplayController : public Component
{
	public:
		inline void setup() override 
		{
			this->tft.init();
			this->spr.createSprite(this->width, this->height);
			this->spr.setSwapBytes(true);
			this->render.setDrawer(spr);
			this->render.setSerial(Serial);
		}

		inline void clearSprite(int color) 
		{
			this->spr.fillRect(0, 0, width, height, color);
		}

		TFT_eSPI tft = TFT_eSPI();
		TFT_eSprite spr = TFT_eSprite(&tft); // Sprite object
		OpenFontRender render;
		int width = 320;
		int height = 170;
	private:
};

DisplayController * display = new DisplayController();

#endif