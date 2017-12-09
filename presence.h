#include <Homie.h>

void presenceLoop();
void presenceSetup();



const int PRESENCE_INTERVAL = 200; // in ms
const int PRESENCE_CALIBRATION_TIME = 30 * 1000; // in ms
const int PRESENCE_TAKE_DOWN_TIME = 3 * 1000;
