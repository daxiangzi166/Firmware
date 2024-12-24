#ifndef SC_WEATHER_H
#define SC_WEATHER_H
#include <Config.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <SC_Config.h>

HTTPClient http;
static String url_xinzhi = "";
static String Weather = "";

int WeatherCode = -1;
float WeatherTemp;
float WeatherHumi;

static unsigned long update_time = 0;


void buildURL(String api, String city) {
    url_xinzhi = "https://api.seniverse.com/v3/weather/now.json?key=";
    url_xinzhi += api;
    url_xinzhi += "&location=";
    url_xinzhi += city;
    url_xinzhi += "&language=en&unit=c";
}

bool getWeather() {
    bool run = false;
    String weather = "";
    JsonDocument doc;
    http.begin(url_xinzhi);
    int httpGet = http.GET();
    if (httpGet > 0) {
        if (httpGet == HTTP_CODE_OK) {
            String json = http.getString();
            deserializeJson(doc, json);
            Weather = doc["results"][0]["now"]["text"].as<String>();
            WeatherCode = doc["results"][0]["now"]["code"].as<int>();
            WeatherTemp = doc["results"][0]["now"]["temperature"].as<int>();
            WeatherHumi = doc["results"][0]["now"]["humidity"].as<int>();
            run = true;
            Serial.println("Success");

        } else if (httpGet == HTTP_CODE_FORBIDDEN) {
            Serial.println("Error");
        }
    }
    http.end();
    return run;
}

float getWeatherTemp()
{
    return WeatherTemp;
}

float getWeatherHumi()
{
    return WeatherHumi;
}

void setup_weather() {
    buildURL(weatherApiKey, weatherCity);
}

void loop_weather(unsigned long currentMillis) {
    if (update_time == 0 || currentMillis - update_time >= WEATHER_INTERVAL) {
        Serial.print("Updating weather...");
        if(getWeather()) {
            Serial.println("Weather updated");
            update_time = currentMillis;
        }
    }
}

void display_weather() {
    displayWeather(Weather);
}
#endif // SC_WEATHER_H