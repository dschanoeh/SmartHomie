#include <Homie.h>
#include "hardware.h"
#include "main.h"
#include "led.h"


#ifdef LED_NODE

uint8_t current;
HomieNode ledNode("led", "led");

boolean isNumeric(String str) {
    unsigned int stringLength = str.length();

    if (stringLength == 0) {
        return false;
    }

    for(unsigned int i = 0; i < stringLength; ++i) {
        if (isDigit(str.charAt(i))) {
            continue;
        }
        return false;
    }
    return true;
}

bool brightnessHandler(const HomieRange& range, const String& value) {
  DEBUG("Brightness handler received " + value + "\n");
  if (!isNumeric(value)) return false;

  uint8_t val = value.toInt();

  if(val>255)
    return false;

  setLED(val);
  return true;
}

bool switchHandler(const HomieRange& range, const String& value) {
  DEBUG("Switch handler received " + value + "\n");

  if(value == "0" && current != 0) {
    setLED(0);
    return true;
  } else if(value == "1" && current == 0) {
    setLED(255);
    return true;
  }

  return false;
}

void preSetupLED() {
  ledNode.advertise("brightness").settable(brightnessHandler);
  ledNode.advertise("switch").settable(switchHandler);
}

void setupLED() {
  pinMode(LED_STRIP_PIN, OUTPUT);
  setLED(LED_INIT_STATE);
}

void setLED(uint8_t value) {
  DEBUG("Adjusting LED value\n");
  analogWrite(LED_STRIP_PIN, value*PWMRANGE/255);
  ledNode.setProperty("brightness").send(String(value));

  if(value == 0) {
    ledNode.setProperty("switch").send("0");
  } else {
    ledNode.setProperty("switch").send("1");
  }
  current = value;
}

void ledLoop() {

}

#endif
