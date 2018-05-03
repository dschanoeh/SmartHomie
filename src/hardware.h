
//#define SONOFF_CONFIG
//#define LIGHT_INTENSITY_CONFIG
//#ifdef TEMP_HUMD_PIR_CONFIG

#ifdef SONOFF_CONFIG
  #define FW_NAME "sh-sonoff"
  #define SONOFF_S20
  #define RELAY_NODE
#endif

#ifdef LIGHT_INTENSITY_CONFIG
  #define FW_NAME "sh-light"
  #define SPARKFUN_THING
  #define LIGHT_INTENSITY_NODE
  #define FUEL_GAUGE
  #define ONE_SHOT
  #define SLEEP_INTERVAL 15 * 60 * 1000 * 1000 // 15 minutes
#endif

#ifdef LED_CONFIG
  #define FW_NAME "sh-led"
  #define WEMOS_D1
  #define LED_NODE
#endif

#ifdef TEMP_HUMD_PIR_CONFIG
  #define FW_NAME "sh-thp"
  #define WEMOS_D1
  #define TEMPERATURE_SENSOR
  #define PRESENCE_DETECTION
#endif

/* Hardware specific pin configuration */
#ifdef WEMOS_D1
  #define PIN_IR 15     //D8 on the board
  #define PIN_SENSOR 16 //D0 on the board
  #define LED_STRIP_PIN 15 //D8 on the board
#endif
#ifdef SPARKFUN_THING
  #define PIN_SENSOR 4  //4 on the board
#endif
#ifdef SONOFF_S20
  #define RELAY_PIN 12
  #define LED_PIN 13
  #define BUTTON_PIN 0
#endif
