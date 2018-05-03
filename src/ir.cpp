#include "hardware.h"
#ifdef IR_TRANSMITTER

#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRtimer.h>
#include <IRutils.h>
#include <Homie.h>
#include "ir.h"
#include "main.h"

IRsend irsend(PIN_IR);
HomieNode irNode("ir","ir");

unsigned long lastIR = 0;

char buffer[64];

/*
 * Strings are encoded as:
 * X YY ZZ
 * X  = 5 or 6 for RC5 or RC6
 * YY = Address of the device
 * ZZ = Command to be issued
 */
bool irTransmitHandler(String value) {
  const char* cstring = value.c_str();
  if(strlen(cstring) != 7) {
    DEBUG("Invalid IR command length");
    return true;
  }

  if(value[0] == '5' && value[1] == ' ') {
    char addrstr[3];
    char commandstr[3];
    addrstr[2] = '\0';
    commandstr[2] = '\0';

    memcpy(addrstr, &cstring[2],2);
    memcpy(commandstr, &cstring[5],2);

    uint8_t addr = strtoul(addrstr,0, 16);
    uint8_t comm = strtoul(commandstr,0, 16);

    sprintf(buffer, "IR addr %x comm %x", addr, comm);
    DEBUG(buffer);
    uint16_t data = irsend.encodeRC5(addr, comm, true);
    sprintf(buffer, "Sending %x", data);
    DEBUG(buffer);
    irsend.sendRC5(data, RC5_BITS, 0);
  } else if(value[0] == '6' && value[1] == ' ') {
    char addrstr[3];
    char commandstr[3];
    addrstr[2] = '\0';
    commandstr[2] = '\0';

    memcpy(addrstr, &cstring[2],2);
    memcpy(commandstr, &cstring[5],2);

    uint8_t addr = strtoul(addrstr,0, 16);
    uint8_t comm = strtoul(commandstr,0, 16);

    sprintf(buffer, "IR addr %x comm %x", addr, comm);
    DEBUG(buffer);
    uint64_t data = irsend.encodeRC6(addr, comm, true);
    sprintf(buffer, "Sending %x", data);
    DEBUG(buffer);
    irsend.sendRC6(data, RC6_MODE0_BITS, 0);
  }

  return true;
}

void irLoop() {
}

void irSetup() {
  irNode.subscribe("transmit", irTransmitHandler);

  DEBUG("IR setup");
  irsend.begin();
}

#endif
