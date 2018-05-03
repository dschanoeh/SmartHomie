#include <Homie.h>
#include "hardware.h"
#include "main.h"
#include "relay.h"


#ifdef RELAY_NODE

bool relay = false;
uint8_t buttonState = 0;
uint8_t lastButtonState = 0;
unsigned long lastDebounceTime = 0;

HomieNode relayNode("switch", "switch");

bool relayHandler(const HomieRange& range, const String& value) {
  DEBUG("Relay handler received " + value + "\n");
  if (value != "true" && value != "false") return false;

  bool cmd = (value == "true");

  setRelay(cmd);
  return true;
}

void preSetupRelay() {
  relayNode.advertise("on").settable(relayHandler);
}

void setupRelay() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_INIT_STATE);
  if(RELAY_INIT_STATE) {
    relay = true;
  } else {
    relay = false;
  }
}

void setRelay(bool value) {
  if(value) {
    DEBUG("Turning relay on\n");
    digitalWrite(RELAY_PIN, HIGH);
    relayNode.setProperty("on").send("true");
  } else {
    DEBUG("Turning relay off\n");
    digitalWrite(RELAY_PIN, LOW);
    relayNode.setProperty("on").send("false");
  }
  relay = value;
}

void relayLoop() {
  /* evaluate button press */
  uint8_t reading = digitalRead(BUTTON_PIN);
  if(reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // button is pressed, toggle relay
      if (buttonState == HIGH) {
        DEBUG("Button toggle\n");
        setRelay(!relay);
      }
    }
  }
  lastButtonState = reading;
}

#endif

