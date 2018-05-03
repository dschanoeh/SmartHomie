#include <Homie.h>

void setupRelay();
void preSetupRelay();

bool relayHandler(const HomieRange& range, const String& value);
void setRelay(bool value);
void relayLoop();

#define DEBOUNCE_DELAY 50
#define RELAY_INIT_STATE 0

