#ifndef SC_TIME_H
#define SC_TIME_H

#include <Config.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
// NTP服务器设置
static WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER);
static unsigned long last_ntp = 0;

bool TimeLoad = false;
int year = 0;
int month = 0;
int day = 0;

bool timeLoad()
{
    struct tm *ti;
    time_t rawtime = timeClient.getEpochTime();
    ti = localtime(&rawtime);
    int year = ti->tm_year + 1900;
    if (year != 1970)
    {
        TimeLoad = true;
        return true;
    }
    else
    {
        return false;
    }
}

String getDate()
{
    return String(year) + "-" + String(month) + "-" + String(day);
}

void setup_time()
{
    Serial.print("Waiting time...");
    timeClient.begin();
    // 更新时间
    timeClient.setUpdateInterval(10 * 60 * 1000);
    // 28800 = +8时区（我们的北京时间）
    timeClient.setTimeOffset(28800);
    while (true)
    {
        if (timeLoad() == false)
        {
            timeClient.update();
            delay(500);
            Serial.print(".");
        }
        else
        {
            Serial.println("");
            Serial.println("Time set success!");
            return;
        }
    }
}

void loop_time(unsigned long currentMillis)
{
    
    // update ntp time
    if (currentMillis - last_ntp >= NTP_UPDATE_INTERVAL)
    {
        Serial.print("Update time...");
        
        last_ntp = currentMillis;
        if (timeClient.update())
        {
            Serial.println("Success");
        }
        else
        {
            Serial.println("Error");
        }
    }

    // 获取时间
    String time = timeClient.getFormattedTime();
    time_t rawtime = timeClient.getEpochTime();
    struct tm *ti;
    ti = localtime(&rawtime);
    year = ti->tm_year + 1900;
    month = ti->tm_mon + 1;
    day = ti->tm_mday;
}

void display_time()
{
    displayDatetime(timeClient.getFormattedTime(), getDate());
}

#endif // SC_TIME_H