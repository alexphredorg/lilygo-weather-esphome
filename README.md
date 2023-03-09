# lilygo-weather-esphome
## Weather display for a LilyGo T-Display-S3 using ESPHome

![](ScreenShot.png)

Tested on ESPHome 2023.2.4 and LilyGo T-Display-S3 (no touch)

Retrieves data from Home Assistant using the AccuWeather forecast (for daily) and Met.No forecast (for hourly).
Press the KEY button to switch to the hourly view, it toggles back to daily after 15 seconds.

Installation:
* Copy lilygo-weather-esphome.yaml to config/esphome
* Create config/esphome/tdisplays3 and put the contents of tdisplays3 folder in there
* Update Yaml to point it to your accuweather (daily) and met.no (hourly) weather forecast entities
* update ESPHome device passwords with unique ones for your installation

Demonstrates the following techniques:
* TFT_ESPi library for drawing on the screen, using double buffering to make it flicker-free
* Scaling TrueType fonts using OpenFontRender
* Bitmap fonts (used for the small monocolor weather graphics)
* Loading and displaying 5/6/5 color sprites (for the larger multicolor weather graphics)
* ESP-side JSON parsing of data coming from Home Assistant
