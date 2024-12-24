#ifndef SC_BOARD_H
#define SC_BOARD_H

#include <Config.h>
#include <Wire.h>
#include <SC_WiFi.h>
#include <SC_SHT4x.h>
#include <SC_Config.h>
#include <esp_log.h>

static unsigned long Reset_startTime = 0;
static bool Reset_buttonPressed = false;

static unsigned long Func_startTime = 0;
static bool Func_buttonPressed = false;

void reset()
{
    ESP.restart();
}

void resetConfig()
{

    wm.resetSettings();
    prefs.begin(AP_NAME);
    prefs.clear();
    prefs.end();
    Serial.println("Reset Settings!");
    
    reset();
}

// 如果功能按键按下
void func()
{
    Serial.println("Press func");
}

void setup_board()
{
    esp_log_level_set("*", ESP_LOG_NONE);
    Serial.begin(115200);
    Wire.begin(SDA_pin, SCL_pin);
    pinMode(RESET_PIN, INPUT_PULLDOWN);
    pinMode(FUNC_PIN, INPUT_PULLDOWN);
    pinMode(BAT_ADC_PIN, INPUT_PULLDOWN);
    pinMode(PLUG_PIN, INPUT_PULLDOWN);
    pinMode(TEMP_OUTPUT_PIN, OUTPUT);
}

void loop_board(unsigned long currentMillis)
{
    if (digitalRead(RESET_PIN) == HIGH)
    {
        if (!Reset_buttonPressed)
        {
            Reset_startTime = currentMillis;
            Reset_buttonPressed = true;
        }
        if ((currentMillis - Reset_startTime) >= 5000)
        {
            resetConfig();
        }
    }
    else
    {
        if (Reset_buttonPressed)
        {
            if ((currentMillis - Reset_startTime) >= 500)
            {
                reset();
            }
            else
            {
                Reset_buttonPressed = false;
            }
        }
    }

    if (digitalRead(RESET_PIN) == HIGH)
    {
        if (!Reset_buttonPressed)
        {
            Reset_startTime = currentMillis;
            Reset_buttonPressed = true;
        }
    }
    else
    {
        if (Reset_buttonPressed)
        {
            if ((currentMillis - Reset_startTime) >= 50)
            {
                func();
            }
            else
            {
                Reset_buttonPressed = false;
            }
        }
    }
    if (sensor_temp > alarmTemp)
    {
        digitalWrite(TEMP_OUTPUT_PIN, HIGH);
    }
    else
    {
        digitalWrite(TEMP_OUTPUT_PIN, LOW);
    }
}

void display_board() {}
#endif // SC_BOARD_H