#ifndef SC_SHT4X_H
#define SC_SHT4X_H
#include <Config.h>
#include <Adafruit_SHT4x.h>
#include <SC_Weather.h>

bool sensor_load = false;
float sensor_temp;
float sensor_hum;


Adafruit_SHT4x sht4 = Adafruit_SHT4x();
void setup_sht4x()
{
    Serial.print("Searching for SHT4x ...");
    if (!sht4.begin(&Wire))
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    int sht4_addr = sht4.readSerial();
    if (sht4_addr == 0x00)
    {
        Serial.println("Not found SHT4x sensor!");
        Serial.println("Sensor data will be replaced by XinZhi API.");
    }
    else
    {
        sensor_load = true;
        sht4.setPrecision(SHT4X_HIGH_PRECISION);
        sht4.setHeater(SHT4X_NO_HEATER);
        Serial.println("");
        Serial.print("Found SHT4x sensor on address 0x");
        Serial.println(sht4_addr, HEX);
    }

}

void loop_sht4x(long currentMillis)
{
    if (sensor_load){
        sensors_event_t humidity, temp;
        sht4.getEvent(&humidity, &temp);
        sensor_temp = temp.temperature;
        sensor_hum = humidity.relative_humidity;
    }
}

void display_sht4x()
{
    if (sensor_load){
        displaySensorData(sensor_temp, sensor_hum);
    }
    else
    {
        displaySensorData(getWeatherTemp(), getWeatherHumi());
    }
}
#endif // SC_SHT4x_H