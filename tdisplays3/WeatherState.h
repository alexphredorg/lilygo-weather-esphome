#ifndef WEATHER_STATE_H
#define WEATHER_STATE_H

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

#define FORECAST_DAYS 5
struct ForecastDay *weatherForecastDaily = new ForecastDay[FORECAST_DAYS];
#define FORECAST_HOURS 12
struct ForecastHour *weatherForecastHourly = new ForecastHour[FORECAST_HOURS];
bool showHourly = false;

#endif