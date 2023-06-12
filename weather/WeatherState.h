#ifndef WEATHER_STATE_H
#define WEATHER_STATE_H

#include <sstream>

#ifndef FORECAST_DAYS
#define FORECAST_DAYS 3
#endif
#ifndef FORECAST_HOURS
#define FORECAST_HOURS 12
#endif 

struct ForecastDay
{
    ForecastDay()
    {
        this->valid = false;
        this->condition = "";
    }

    bool valid;
    int precip_probability;
    int temp_low;
    int temp_high;
    std::string condition;
    std::string day;
};

struct ForecastHour
{
    ForecastHour()
    {
        this->valid = false;
        this->condition = "";
    }
    
    bool valid;
    int temp;
    std::string condition;
    float precip;
    int hour;
};

struct ForecastDay *weatherForecastDaily = new ForecastDay[FORECAST_DAYS];
struct ForecastHour *weatherForecastHourly = new ForecastHour[FORECAST_HOURS];
bool showHourly = false;

void parseHourlyForecast(std::string rawJson)
{
    DynamicJsonDocument doc(16384);
    std::istringstream st(rawJson);
    auto error = deserializeJson(doc, st /* updated value */);
    if (!error) 
    {
        JsonArray array = doc.as<JsonArray>();
        int i = 0;
        time_t t = std::time(NULL);
        struct tm *ts = localtime(&t);
        int hour = ts->tm_hour;
        for(JsonVariant v : array) 
        {
            JsonObject obj = v.as<JsonObject>();
            if (i >= FORECAST_HOURS) break;
            weatherForecastHourly[i].temp = obj["temperature"].as<int>();
            weatherForecastHourly[i].precip = obj["precipitation"].as<float>();
            weatherForecastHourly[i].condition = obj["condition"].as<std::string>();
            weatherForecastHourly[i].hour = 1 + ((hour + i) % 12);
            weatherForecastHourly[i].valid = true;
            ESP_LOGD("lilygo", "%i: %i %i %f %s %s", i, hour, weatherForecastHourly[i].temp, weatherForecastHourly[i].precip, weatherForecastHourly[i].condition.c_str(), obj["datetime"].as<std::string>().c_str());
            i++;
        }
    }
    else
    {
        ESP_LOGW("lilygo", "deserializeJson returned %s", error.c_str());
        char next[100];
        st.seekg(-20, st.cur);
        st.getline(next, 100);
        ESP_LOGW("lilygo", "error in 20 chars: %s", next);
    }
}

void parseDailyForecast(std::string rawJson)
{
    // parse weather from AccuWeather
    DynamicJsonDocument doc(16384);
    std::istringstream st(rawJson);
    auto error = deserializeJson(doc, st /* updated value */);
    if (!error) {
        JsonArray array = doc.as<JsonArray>();
        int i = 0;
        time_t t = std::time(NULL);
        struct tm *ts = localtime(&t);
        int wday = ts->tm_wday;
        for(JsonVariant v : array) 
        {
            JsonObject obj = v.as<JsonObject>();
            if (i >= FORECAST_DAYS) break;
            weatherForecastDaily[i].temp_low = obj["templow"].as<int>();
            weatherForecastDaily[i].temp_high = obj["temperature"].as<int>();
            weatherForecastDaily[i].precip_probability = obj["precipitation_probability"].as<float>();
            weatherForecastDaily[i].condition = obj["condition"].as<std::string>();
            weatherForecastDaily[i].valid = true;
            // this hack assumes that the first forecast is for today, and they increment one per day
            // that isn't true for all forecast arrays on HomeAssistant, but works for AccuWeather
            switch ((wday + i) % 7)
            {
                case 0:  weatherForecastDaily[i].day = "Sun"; break;
                case 1:  weatherForecastDaily[i].day = "Mon"; break;
                case 2:  weatherForecastDaily[i].day = "Tue"; break;
                case 3:  weatherForecastDaily[i].day = "Wed"; break;
                case 4:  weatherForecastDaily[i].day = "Thu"; break;
                case 5:  weatherForecastDaily[i].day = "Fri"; break;
                case 6:  weatherForecastDaily[i].day = "Sat"; break;
                default: weatherForecastDaily[i].day = "???"; break;
            }
            ESP_LOGD("lilygo", "%i: %i->%i %i %s, %s", i, weatherForecastDaily[i].temp_low, weatherForecastDaily[i].temp_high, weatherForecastDaily[i].precip_probability, weatherForecastDaily[i].day.c_str(), weatherForecastDaily[i].condition.c_str());
            i++;
        }
    }
    else
    {
        ESP_LOGW("lilygo", "deserializeJson returned %s", error.c_str());
        char next[100];
        st.seekg(-20, st.cur);
        st.getline(next, 100);
        ESP_LOGW("lilygo", "error in 20 chars: %s", next);
    }
}

std::map<std::string, std::string> weatherIconMapString =
{
    //Weather forecast Icon
    { "clear-night", 	"\U0000f159" },
    { "cloudy", 		"\U0000f15b" },
    { "partlycloudy", 	"\U0000f172" },
    { "fog",	 	    "\U0000e818" },
    { "hail",	 	    "\U0000f67f" },
    { "lightning",	    "\U0000ebdb" },
    { "lightning-rainy","\U0000ebdb" },
    { "pouring",		"\U0000f61f" },
    { "rainy", 		    "\U0000f61e" },
    { "snowy", 		    "\U0000f61c" },
    { "snowy-rainy", 	"\U0000f61d" },
    { "sunny", 		    "\U0000e81a" },
    { "windy", 		    "\U0000efd8" },
    { "windy-variant", 	"\U0000efd8" },
    { "exceptional", 	"\U0000f7f3" }
};

std::map<std::string, Color> weatherIconMapColor =
{
    { "clear-night", 	Color(255, 255, 191) },
    { "cloudy", 		Color(127, 127, 127) },
    { "partlycloudy", 	Color(191, 191, 191) },
    { "fog",	 	    Color(127, 127, 127) },
    { "hail",	 	    Color(191, 191, 191) },
    { "lightning",	    Color(255, 255, 191) },
    { "lightning-rainy",Color(255, 255, 191) },
    { "pouring",		Color(127, 127, 255) },
    { "rainy", 		    Color(127, 127, 255) },
    { "snowy", 		    Color(255, 255, 255) },
    { "snowy-rainy", 	Color(127, 127, 255) },
    { "sunny", 		    Color(255, 255, 127) },
    { "windy", 		    Color(191, 191, 191) },
    { "windy-variant", 	Color(191, 191, 191) },
    { "exceptional", 	Color(191, 191, 191) }
};
#endif