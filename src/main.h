#include <Homie.h>
#include "version.h"

//#define DEBUG_BUILD

#ifdef DEBUG_BUILD
#  define DEBUG(x) Serial.println(x);
#else
#  define DEBUG(x) do {} while (0);
#endif
