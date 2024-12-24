#ifndef SC_CONFIG_H
#define SC_CONFIG_H
#include <Preferences.h>
#include <SC_WiFi.h>

int alarmTemp;

String weatherApiKey;
String weatherCity;

String mqttServer;
int mqttPort;
String mqttUser;
String mqttPass;
String mqttTopic;

Preferences prefs;


extern WiFiManager wm;

WiFiManagerParameter alarmTempParam("alarm_temp", "Alarm Temperature", "40", 2);

WiFiManagerParameter weatherApiKeyParam("weather_api_key", "Seniverse API Key", "", 40);
WiFiManagerParameter weatherCityParam("city", "Weather City", "ZhejiangHangzhou", 20);

WiFiManagerParameter mqttServerParam("server", "MQTT Server", "", 40);
WiFiManagerParameter mqttPortParam("port", "MQTT Port", "1883", 6);
WiFiManagerParameter mqttUserParam("user", "MQTT User", "", 20);
WiFiManagerParameter mqttPassParam("pass", "MQTT Password", "", 20);
WiFiManagerParameter mqttTopicParam("topic", "MQTT Topic", "home/SmartClock", 20);


WiFiManagerParameter writeParam("write_param", "Overwrite parameter(0/1)", "0", 1);

void setup_config() {
    wm.addParameter(&alarmTempParam);

    wm.addParameter(&weatherApiKeyParam);
    wm.addParameter(&weatherCityParam);

    wm.addParameter(&mqttServerParam);
    wm.addParameter(&mqttPortParam);
    wm.addParameter(&mqttUserParam);
    wm.addParameter(&mqttPassParam);
    wm.addParameter(&mqttTopicParam);
    wm.addParameter(&writeParam);
}

void loop_config(long currentMillis){}

void display_config(){}

void get_config() {
    prefs.begin(AP_NAME);
    int write_data = atoi(writeParam.getValue());
    if (write_data == 1 || prefs.getUInt("start_num", 0) == 0)
    {
        prefs.putUInt("start_num", 1);

        prefs.putUInt("alarmTemp", atoi(alarmTempParam.getValue()));

        prefs.putString("weatherApiKey", weatherApiKeyParam.getValue());
        prefs.putString("weatherCity", weatherCityParam.getValue());

        prefs.putString("mqttServer", mqttServerParam.getValue());
        prefs.putInt("mqttPort", atoi(mqttPortParam.getValue()));
        prefs.putString("mqttUser", mqttUserParam.getValue());
        prefs.putString("mqttPass", mqttPassParam.getValue());
    }

    prefs.putUInt("start_num", prefs.getUInt("start_num", 0) + 1);

    alarmTemp = prefs.getUInt("alarmTemp", 40);

    weatherApiKey = prefs.getString("weatherApiKey", "");
    weatherCity = prefs.getString("weatherCity", "");

    mqttServer = prefs.getString("mqttServer", "");
    mqttPort = prefs.getInt("mqttPort", 1883);
    mqttUser = prefs.getString("mqttUser", "");
    mqttPass = prefs.getString("mqttPass", "");

    prefs.end();
}

#endif