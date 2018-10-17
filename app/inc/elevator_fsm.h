#ifndef APP_INC_ELEVATOR_FSM_H
#define APP_INC_ELEVATOR_FSM_H

#include "sapi.h"

#define LOW_FLOOR       0
#define FIRST_FLOOR     1
#define SECOND_FLOOR    2

typedef enum {
	LOW_FLOOR_STATE,
    GOING_UP_STATE,
    STOPPED_STATE,
    GOING_DOWN_STATE
} ElevatorFsmState;

void initElevatorFsm();

void updateElevatorFsm(gpioMap_t key);

#endif
