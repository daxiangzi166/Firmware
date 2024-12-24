// 板名称
#define AP_NAME "SmartClock"

// NTP服务器设置
#define NTP_SERVER "ntp1.aliyun.com"
#define NTP_UPDATE_INTERVAL 10*60*1000
// 时区设置
#define TIME_OFFSET 28800

// 板配置
#define RESET_PIN 19
#define FUNC_PIN 18
#define PLUG_PIN 32
#define BAT_ADC_PIN 33
#define TEMP_OUTPUT_PIN 13

// ADC 配置
#define ADC_RESOLUTION 4095.0
#define ADC_VREF 3.3
#define ADC_OFFSET 0.0


// i2c 设置
#define SDA_pin 25
#define SCL_pin 33

// 电池配置
#define BAT_FULL_VOL 4.2
#define BAT_EMPTY_VOL 3.5
#define BAT_UP_REG 1500.00
#define BAT_DOWN_REG 3300.00

// OLED显示屏设置
#define SCREEN_ADDRESS  0x3C
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define SCREEN_RESET    -1


// MQTT 配置
#define MQTT_PUBLISH_INTERVAL 60*1000

// WIFI配置
#define WIFI_RECONNECT_INTERVAL 30*1000

// 天气API配置
#define WEATHER_INTERVAL 2*60*60*1000