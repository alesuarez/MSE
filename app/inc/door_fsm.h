#ifndef APP_INC_DOOR_FSM_H_
#define APP_INC_DOOR_FSM_H_

#include "sapi.h"

#define ZERO_TIME 0

typedef enum {
	CLOSED_STATE,
    OPENING_STATE,
    OPEN_STATE,
    CLOSING_STATE,
    STOPPED_STATE
} DoorFsmState;


void initDoorFsm();
void updateDoorFsm(gpioMap_t * key);
void updateRgbLedDoor();

#endif
