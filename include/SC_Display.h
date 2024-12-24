#ifndef SC_DISPLAY_H
#define SC_DISPLAY_H
#include <Config.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SC_Pic.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_RESET);

void display_start()
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    delay(100); // clear 太快会导致没清屏就完成就写入
}

void display_end()
{
    display.display();
}

void reset_page_display(String wifi_ssid, String wifi_ip)
{
    display_start();

    // 边框
    display.drawRect(0, 0, 128, 64, WHITE);
    display.drawRect(1, 1, 126, 62, WHITE);

    // 主体
    display.setTextSize(1);
    display.setCursor(4, 4);
    display.print("RESET CONFIG PAGE");

    display.setTextSize(1);
    display.setCursor(5, 20);
    display.print("SSID:");

    display.setTextSize(1);
    display.setCursor(5, 30);
    display.print(wifi_ssid);

    display.setTextSize(1);
    display.setCursor(5, 40);
    display.print("WEB_SERVER:");

    display.setTextSize(1);
    display.setCursor(5, 50);
    String serverWeb = "http://" + wifi_ip;
    display.print(serverWeb.c_str());

    display_end();
}

void displaySensorData(float temperature, float humidity)
{
    // 温度
    display.setTextSize(1);
    display.setCursor(5, 42);
    display.print("Temp:");
    display.print(temperature, 1);
    display.print("C");

    // 湿度
    display.setTextSize(1);
    display.setCursor(5, 52);
    display.print("Humi:");
    display.print(humidity, 1);
    display.print("%");
}

void displayDatetime(String time, String date)
{
    // 时间
    display.setTextSize(2);
    display.setCursor(10, 5);
    display.print(time);

    // 日期
    display.setTextSize(1);
    display.setCursor(35, 22);
    display.print(date);
}

void displayWifiLogo(int wifi_rssi_code)
{
    int p_x = 115;
    int p_y = 5;
    display.drawBitmap(p_x, p_y, wifi_logo_allArray[wifi_rssi_code], 7, 7, WHITE);
}

void displayPlugLogo(int plug_status_code)
{
    int p_x = 115;
    int p_y = 25;
    display.drawBitmap(p_x, p_y, bitmap_plug_in_allArray[plug_status_code], 7, 7, WHITE);
}

void displayBatteryLogo(int battery_status_code)
{
    int p_x = 115;
    int p_y = 25;
    display.drawBitmap(p_x, p_y, bitmap_battery_allArray[battery_status_code], 7, 7, WHITE);
}

void displayMqttLogo(int mqtt_status_code)
{
    int p_x = 115;
    int p_y = 15;
    display.drawBitmap(p_x, p_y, bitmap_server_allArray[mqtt_status_code], 7, 7, WHITE);
}

void displayWeather(String Weather)
{
    display.setTextSize(1);
    display.setCursor(5, 32);
    display.print("WX:");
    display.print(Weather);
}

void setup_display()
{
    Serial.println("Start SSD1306 OLED Display");
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, false, false))
    {
        Serial.println("SSD1306 allocation failed");
        for (;;)
            ;
    }
    display_start();
    display.drawBitmap(0, 0, start_logo, 128, 64, WHITE);
    display_end();
}

void loop_display(unsigned long currentMillis)
{
    display_start();

    // 边框
    display.drawRect(0, 0, 128, 64, WHITE);
    display.drawRect(1, 1, 126, 62, WHITE);
}
#endif
