#ifndef APP_INC_LED_SERVICE_H_
#define APP_INC_LED_SERVICE_H_

#include "sapi.h"
#include "door_fsm.h"

void actualDoorLedIndicator(DoorFsmState doorState);
void rgbRedStatus(DoorFsmState doorState);

#endif
