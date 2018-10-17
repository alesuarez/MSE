#ifndef APP_INC_LED_SERVICE_H_
#define APP_INC_LED_SERVICE_H_

#include "sapi.h"
#include "elevator_fsm.h"

void actualFloorLedIndicator(uint16_t floor);
void motorStateIndicator(ElevatorFsmState elevatorFsmState);

#endif
