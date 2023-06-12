# lilygo-weather-esphome
## Weather display for a LilyGo T-Display-S3 using ESPHome

![](ScreenShot.png)

Tested on ESPHome 2023.2.4 and LilyGo T-Display-S3 (no touch)

Retrieves data from Home Assistant using the AccuWeather forecast (for daily) and Met.No forecast (for hourly).
Press the KEY button to switch to the hourly view, it toggles back to daily after 15 seconds.

Installation:
* Copy lilygo-weather-esphome.yaml to config/esphome
* Create config/esphome/weather and put the contents of weather folder in there
* Update Yaml to point it to your accuweather (daily) and met.no (hourly) weather forecast entities
* update ESPHome device passwords with unique ones for your installation

