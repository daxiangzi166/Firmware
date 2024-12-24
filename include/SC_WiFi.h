#ifndef SC_WIFI_H
#define SC_WIFI_H
#include <Config.h>
#include <cstdlib>
#include <WiFi.h>
#include <WiFiManager.h>
#include <SC_Display.h>
#include <SC_Config.h>

unsigned long no_wifi_time = 0;
int wifi_status;

WiFiManager wm;

void saveConfigCallback() {
  Serial.println("Should save config");
}

void configModeCallback(WiFiManager *myWiFiManager)
{
    String wifi_ssid = myWiFiManager->getConfigPortalSSID();
    String wifi_ip = WiFi.softAPIP().toString();
    Serial.print("Please connect WiFi(");
    Serial.print(wifi_ssid);
    Serial.println(") to reset config.");
    Serial.print("Serverip: ");
    Serial.println(wifi_ip);
    reset_page_display(wifi_ssid, wifi_ip);
}

void setup_wifi()
{
    Serial.print("Connecting to WiFi...");

    wm.setDebugOutput(false);
    wm.setAPCallback(configModeCallback);
    wm.setSaveConfigCallback(saveConfigCallback);
    wm.setHostname(AP_NAME);
    // 自动连接到保存的网络，如果失败，则启动配置Portal
    bool res;
    res = wm.autoConnect(AP_NAME);

    if (!res)
    {
        // 重置并尝试重新连接
        ESP.restart();
    }
    else
    {
        Serial.println("");
        // 如果连接成功
        Serial.println("Connected to Wi-Fi successfully");
    }

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    
    Serial.print("WIFI IP: ");
    Serial.println(WiFi.localIP());
    WiFi.setAutoConnect(true);
}

void loop_wifi(unsigned long currentMillis)
{
    // WIFI reconnect
    if (WiFi.status() != WL_CONNECTED)
    {
        if (no_wifi_time == 0)
        {
            no_wifi_time = currentMillis;
        }
        else
        {
            if (currentMillis - no_wifi_time >= WIFI_RECONNECT_INTERVAL)
            {
                Serial.println("WiFi not connected, reconnecting...");
                WiFi.reconnect();
                no_wifi_time = 0;
            }
        }
    }

    // 显示WIFI
    long rssi = WiFi.RSSI();
    // 根据Wi-Fi信号强度选择图片
    if (WiFi.status() == WL_CONNECTED)
    {
        if (-70 < rssi)
        {
            wifi_status = WIFI_RSSI_HIGH_CODE;
        }
        else if (-90 < rssi)
        {
            wifi_status = WIFI_RSSI_MEDIUM_CODE;
        }
        else
        {
            wifi_status = WIFI_RSSI_LOW_CODE;
        }
    }
    else
    {
        wifi_status = WIFI_RSSI_NONE_CODE;
    }
}

void display_wifi()
{
    displayWifiLogo(wifi_status);
}
#endif