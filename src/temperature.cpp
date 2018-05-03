#include "hardware.h"
#ifdef TEMPERATURE_SENSOR

#include <Homie.h>
#include "temperature.h"
#include "main.h"
#include "HTU21D.h"

HTU21D myHumidity;

unsigned long wait_till = 0;
float humd = 0.0f;
float temp = 0.0f;
int temperature_state = 0;

/* 0 between readings
   1 request humidity
   2 read humidity
   3 request temperature
   4 read temperature
   5 send
*/

HomieNode temperatureNode("temperature", "temperature");
HomieNode humidityNode("humidity", "humidity");

void temperatureSetup() {
  temperatureNode.setProperty("unit").send("c");
  humidityNode.setProperty("unit").send("percent");

  myHumidity.begin(); /* TODO maybe this needs to be called after homie setup */
}

void temperatureLoop() {

    switch(temperature_state) {
      case 0:
        temperature_state = 1;
        break;
      case 1:
        DEBUG("# Request Humidity");
        myHumidity.requestHumidity();
        temperature_state = 2;
        wait_till = millis() + 55UL;
        break;
      case 2:
        if (millis() > wait_till) {
          DEBUG("# Read Humidity");
          humd = myHumidity.readHumidity();
          temperature_state = 3;
        }
        break;
      case 3:
        DEBUG("# Request Temperature");
        myHumidity.requestTemperature();
        temperature_state = 4;
        wait_till = millis() + 55UL;
        break;
      case 4:
        if (millis() > wait_till) {
          DEBUG("# Read Temperature");
          temp = myHumidity.readTemperature();
          temperature_state = 5;
        }
        break;
      case 5:
        //DEBUGF("Temperature: %f C", temp);
        //DEBUGF("Humidity: %f", humd);
        temperatureNode.setProperty("degrees").send(String(temp)));
        humidityNode.setProperty("percent").send(String(humd)));
        wait_till = millis() + TEMPERATURE_INTERVAL;
        temperature_state = 6;
        break;
      case 6: /* limbo state that we'll only get out of after waking up */
        if (millis() > wait_till) {
          temperature_state = 0;
        }
        break;
      default:
        temperature_state=0;
        break;
    } 
}

#endif

