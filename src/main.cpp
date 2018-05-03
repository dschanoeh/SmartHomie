#include <Homie.h>
#include "hardware.h"
#include "main.h"
#include "presence.h"
#include "temperature.h"
#include "ir.h"
#include "fuelgauge.h"
#include "relay.h"
#include "light_intensity.h"
#include "led.h"

void loopHandler() {
#ifdef ONE_SHOT
  /* if we are in one shot mode, the loop handler doesn't get executed */
  return;
#endif

#ifdef PRESENCE_DETECTION
  presenceLoop();
#endif
#ifdef TEMPERATURE_SENSOR
  temperatureLoop();
#endif
#ifdef IR_TRANSMITTER
  irLoop();
#endif
#ifdef FUEL_GAUGE
  postBatteryUpdate();
#endif
#ifdef RELAY_NODE
  relayLoop();
#endif
#ifdef LED_NODE
  ledLoop();
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
#ifdef FUEL_GAUGE
  fuelGaugeSetup();
#endif
#ifdef RELAY_NODE
  setupRelay();
#endif
#ifdef LED_NODE
  setupLED();
#endif
#ifdef LIGHT_INTENSITY_NODE
  lightIntensitySetup();
#endif
}

void doOnce() {
  #ifdef LIGHT_INTENSITY_NODE
    postlightIntensityUpdate();
  #endif
  #ifdef FUEL_GAUGE
    postBatteryUpdate();
  #endif
}

void onHomieEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_READY:
      DEBUG("MQTT connected...");
      #ifdef ONE_SHOT
      doOnce();
      Homie.prepareToSleep();
      #endif
      break;
#ifdef ONE_SHOT
    case HomieEventType::READY_TO_SLEEP:
      Homie.getLogger() << "Ready to sleep" << endl;
      Homie.doDeepSleep(SLEEP_INTERVAL);
      break;
#endif
  }
}

void setup() {
#ifdef SONOFF_S20
  Homie.setLedPin(LED_PIN, HIGH);
  Homie.setResetTrigger(BUTTON_PIN, LOW, 5000);
#endif
  Serial.begin(115200);
  DEBUG("STARTING")
  Homie_setFirmware(FW_NAME, FW_VERSION);
#ifndef DEBUG_BUILD
  Homie.disableLedFeedback();
#endif

#ifdef IR_TRANSMITTER
  Homie.registerNode(irNode);
#endif
#ifdef RELAY_NODE
  preSetupRelay();
#endif
#ifdef LED_NODE
  preSetupLED();
#endif


  Homie_setBrand("SmartHomie");
  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);
  Homie.onEvent(onHomieEvent);
  Homie.setup();
}

void loop() {
  Homie.loop();
}
