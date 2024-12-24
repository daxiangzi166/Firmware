#ifndef SC_MQTT_H
#define SC_MQTT_H
#include <Config.h>
#include <PubSubClient.h>
#include <SC_WiFi.h>
#include <SC_Display.h>
#include <SC_Config.h>
#include <SC_SHT4x.h>

// MQTT 配置
static WiFiClient tcpClient;
PubSubClient mqttClient(tcpClient);

int mqtt_status;
static unsigned long previousConnectMillis = 0;
static unsigned long previousPublishMillis = 0;
// MQTT回调
void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    Serial.printf("Message arrived in topic %s, length %d\n", topic, length);
    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
}

// MQTT 配置
void setup_mqtt()
{
    mqttClient.setServer(mqttServerParam.getValue(), atoi(mqttPortParam.getValue()));
    mqttClient.setCallback(mqtt_callback);
}


void loop_mqtt(unsigned long currentMillis){
    // 连接MQTT服务器
    if (!mqttClient.connected())
    {
        mqtt_status = SERVER_DISCONNECTED_CODE;
        if (currentMillis - previousConnectMillis > MQTT_PUBLISH_INTERVAL)
        {
            previousConnectMillis = currentMillis;
            if (mqttClient.connect(AP_NAME, mqttUser.c_str(), mqttPass.c_str()))
            {
                mqttClient.publish(mqttTopic.c_str(), "Hello, MQTT Server!");
                mqttClient.subscribe(mqttTopic.c_str()); 
            }
        }
    }

    // 定期发送消息
    if (mqttClient.connected())
    {
        mqtt_status = SERVER_CONNECTED_CODE;
        if (currentMillis - previousPublishMillis >= MQTT_PUBLISH_INTERVAL)
        {
            previousPublishMillis = currentMillis;
            String tempStr = String(sensor_temp, 1) + "," + String(sensor_hum, 1);
            mqttClient.publish(mqttTopic.c_str(), tempStr.c_str());
        }
    }
  mqttClient.loop();
}

void display_mqtt(){
    displayMqttLogo(mqtt_status);
}

#endif // SC_MQTT_H