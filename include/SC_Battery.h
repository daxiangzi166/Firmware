#ifndef SC_BATTERY_H
#define SC_BATTERY_H
#include <Config.h>
#include <SC_Display.h>

int plug_status;
int battery_status;

float getPinVoltage(int pin)
{
    float pin_vol = analogRead(pin) * (ADC_VREF / ADC_RESOLUTION) + ADC_OFFSET;
    return pin_vol;
}

float calcVoltage(int pin, float up_reg, float down_reg)
{
    float adc_vol = getPinVoltage(pin);
    float calc_vol = adc_vol / down_reg * (up_reg + down_reg);
    return calc_vol;
}

int getBatVolPrecent()
{
    float bat_vol = round(calcVoltage(BAT_ADC_PIN, BAT_UP_REG, BAT_DOWN_REG) * 10) / 10;
    if (bat_vol >= BAT_FULL_VOL)
    {
        return 100;
    }
    else
    {
        int bat_percent = (1 - ((BAT_FULL_VOL - bat_vol) / (BAT_FULL_VOL - BAT_EMPTY_VOL))) * 100;
        bat_percent = constrain(bat_percent, 0, 100);
        return bat_percent;
    }
}

void loop_battery(unsigned long currentMillis)
{
    int bat_percent = getBatVolPrecent();
    if (digitalRead(PLUG_PIN) == HIGH)
    {
        plug_status = PLUG_IN_TRUE_CODE;
    }
    else
    {
        plug_status = PLUG_IN_FALSE_CODE;
        if (bat_percent >= 65)
        {
            
            battery_status = BAT_PERCENT_HIGH_CODE;
        }
        else if (bat_percent >= 50)
        {
            battery_status = BAT_PERCENT_MEDIUM_CODE;
        }
        else if (bat_percent >= 25)
        {
            battery_status = BAT_PERCENT_LOW_CODE;
        }
        else
        {
            battery_status = BAT_PERCENT_ERROR_CODE;
        }
    }

}

void display_battery()
{
    if (plug_status == PLUG_IN_TRUE_CODE)
    {
        displayPlugLogo(PLUG_IN_TRUE_CODE);
    }
    else
    {
        displayBatteryLogo(battery_status);
    }
}

#endif // SC_BATTERY_H