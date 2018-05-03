#include "hardware.h"
#ifdef FUEL_GAUGE
#include <Wire.h>
#include "LiFuelGauge.h"
#include "fuelgauge.h"

LiFuelGauge gauge(MAX17043);

HomieNode batterySoCNode("battery", "soc");
HomieNode batteryVoltageNode("battery", "voltage");
unsigned long fg_wait_till = 0;

void fuelGaugeSetup() {
  gauge.reset();
  batterySoCNode.setProperty("unit").send("percent");
  batteryVoltageNode.setProperty("unit").send("V");
}

void postBatteryUpdate() {
  gauge.wake();
  batterySoCNode.setProperty("percent").send(String(gauge.getSOC(),0));
  batteryVoltageNode.setProperty("V").send(String(gauge.getVoltage(),2));
  gauge.sleep();
}

#endif
