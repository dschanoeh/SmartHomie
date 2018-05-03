#include <Homie.h>

void setupLED();
void preSetupLED();

bool ledHandler(const HomieRange& range, const String& value);
void setLED(uint8_t value);
void ledLoop();

#define LED_INIT_STATE 0
