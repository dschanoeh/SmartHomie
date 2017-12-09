#include "hardware.h";
#ifdef PRESENCE_DETECTION

#include <Homie.h>
#include "presence.h";
#include "main.h";

HomieNode presenceNode("presence", "presence");

unsigned long lastPresenceRead = 0;
unsigned long calibrationFinished = 0;

bool currentPresence = false;
unsigned long lastPositivePresence = 0;

void presenceLoop() {
  unsigned long now = millis();

  /* don't do anything until calibration time has passed */
  if(calibrationFinished == 0) {
    calibrationFinished = now + PRESENCE_CALIBRATION_TIME;
  }
  if(now < calibrationFinished) {
    return;
  }

  if (now - lastPresenceRead >= PRESENCE_INTERVAL || lastPresenceRead == 0) {
    int res = digitalRead(PIN_SENSOR);
    if(res == HIGH) {
      if(currentPresence != true) {
        currentPresence = true;
        DEBUG("Presence detected");
        Homie.setNodeProperty(presenceNode, "value", "1", true);
      }
      lastPositivePresence = now;
    } else {
      if(now > (lastPositivePresence + PRESENCE_TAKE_DOWN_TIME) && currentPresence == true) {
        currentPresence = false;
        DEBUG("No more presence");
        Homie.setNodeProperty(presenceNode, "value", "0", true);
      }
    }
    lastPresenceRead = now;
  }
}

void presenceSetup() {
  DEBUG("Presence setup");

  pinMode(PIN_SENSOR, INPUT);
  Homie.setNodeProperty(presenceNode, "unit", "bool", true);
}

#endif

