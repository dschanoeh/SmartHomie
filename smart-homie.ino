#include <Homie.h>
#include "hardware.h"
#include "main.h"
#include "presence.h"
#include "temperature.h"
#include "ir.h"


void loopHandler() {
#ifdef PRESENCE_DETECTION
  presenceLoop();
#endif
#ifdef TEMPERATURE_SENSOR
  temperatureLoop();
#endif
#ifdef IR_TRANSMITTER
  irLoop();
#endif
}

void setupHandler() {
#ifdef PRESENCE_DETECTION
  presenceSetup();
#endif
#ifdef TEMPERATURE_SENSOR
  temperatureSetup();
#endif
#ifdef IR_TRANSMITTER
  irSetup();
#endif
}

void onHomieEvent(HomieEvent event) {
  switch(event) {
    case HOMIE_MQTT_CONNECTED:
      DEBUG("MQTT connected...");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Homie.setFirmware(FW_NAME, FW_VERSION);
#ifndef DEBUG_BUILD
  Homie.enableBuiltInLedIndicator(false);
#endif

#ifdef IR_TRANSMITTER
  Homie.registerNode(irNode);
#endif
  
  Homie.setBrand("SmartHomie");
  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);
  Homie.onEvent(onHomieEvent);
  Homie.setup();
}

void loop() {
  Homie.loop();
}
