#include <Arduino.h>
#include <SC_Board.h>
#include <SC_Display.h>
#include <SC_WiFi.h>
#include <SC_Mqtt.h>
#include <SC_Time.h>
#include <SC_Sht4x.h>
#include <SC_Battery.h>
#include <SC_Weather.h>
#include <Config.h>


void setup() {

  setup_board();
  setup_display();
  setup_config();
  setup_wifi();
  get_config();
  setup_mqtt();
  setup_time();
  setup_sht4x();
  setup_weather();

  Serial.println("Setup finished!");
  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();
  
  loop_board(currentMillis);
  loop_config(currentMillis);
  loop_time(currentMillis);
  loop_battery(currentMillis);
  loop_display(currentMillis);
  loop_wifi(currentMillis);
  loop_sht4x(currentMillis);
  loop_weather(currentMillis);
  loop_mqtt(currentMillis);

  display_battery();
  display_board();
  display_config();
  display_mqtt();
  display_sht4x();
  display_time();
  display_weather();
  display_wifi();

  display_end();
  delay(200);
}