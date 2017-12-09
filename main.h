#include <Homie.h>
#include "version.h"

//#define DEBUG_BUILD

#define FW_NAME "smart-homie"

#ifdef DEBUG_BUILD
#  define DEBUG(x) Serial.println(x);
#else
#  define DEBUG(x) do {} while (0)
#endif
