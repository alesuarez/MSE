#ifndef APP_INC_KEY_SERVICE_H_
#define APP_INC_KEY_SERVICE_H_

#include "sapi.h"

bool_t isPress(gpioMap_t key);
bool_t notPress(gpioMap_t key);
void buttonPressed(gpioMap_t tecla);
void buttonReleased(gpioMap_t key);

#endif
