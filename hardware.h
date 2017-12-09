
/*
 * Select the board you are using
 */
#define WEMOS_D1
//#define SPARKFUN_THING
//#define SONOFF_S20

/*
 * Select the connected hardware
 */
#define TEMPERATURE_SENSOR
#define IR_TRANSMITTER
#define PRESENCE_DETECTION


#ifdef WEMOS_D1
  #define PIN_IR 15     //D8 on the board
  #define PIN_SENSOR 16 //D0 on the board
#endif
#ifdef SPARKFUN_THING
  #define PIN_SENSOR 4  //4 on the board
#endif
#ifdef SONOFF_S20
  #define RELAY_PIN 12
  #define LED_PIN 13
  #define BUTTON_PIN 0
#endif
