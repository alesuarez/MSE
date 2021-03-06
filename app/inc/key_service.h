#ifndef APP_INC_KEY_SERVICE_H_
#define APP_INC_KEY_SERVICE_H_

#include "sapi.h"

#define LOW_FLOOR_KEY       TEC1
#define FIRST_FLOOR_KEY     TEC2
#define SECOND_FLOOR_KEY    TEC3
#define MOTOR_KEY           TEC4

bool_t isPress(gpioMap_t key);
bool_t notPress(gpioMap_t key);

bool_t buttonPressed(gpioMap_t key);
bool_t buttonReleased(gpioMap_t key);
uint16_t mapKeyToFloor(gpioMap_t key);

#endif
