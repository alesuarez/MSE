#include "elevator_fsm.h"
#include "key_service.h"
#include "led_service.h"

#define DEFAULT_MAX_STOPPED_10_SEG 250
#define ZERO 0

ElevatorFsmState actualElevatorFsmState;

static bool_t isAcctionKey(gpioMap_t key);

void initElevatorFsm() {
    actualElevatorFsmState = LOW_FLOOR_STATE;
}

void updateElevatorFsm(gpioMap_t key) {
    static uint16_t actualFloor = LOW_FLOOR;
    static uint16_t requiredFloor = LOW_FLOOR;
    static uint16_t stoppedTime = ZERO;

    switch (actualElevatorFsmState) {

        case LOW_FLOOR_STATE:
            if (isAcctionKey(key)) {
                requiredFloor = mapKeyToFloor(key);
                actualElevatorFsmState = GOING_UP_STATE;
            }
            break;

        case GOING_UP_STATE:
            if (requiredFloor == actualFloor) {
                actualElevatorFsmState = STOPPED_STATE;
            } else if (key == MOTOR_KEY) {
                actualFloor++;
            }
            break;

        case STOPPED_STATE:
            if (stoppedTime >= DEFAULT_MAX_STOPPED_10_SEG) {
                requiredFloor = LOW_FLOOR;
                stoppedTime = ZERO;
                actualElevatorFsmState = GOING_DOWN_STATE;
            } else if (isAcctionKey(key)){
                if (actualFloor - requiredFloor > ZERO) {
                    actualElevatorFsmState = GOING_DOWN_STATE;
                } else {
                    actualElevatorFsmState = GOING_UP_STATE;
                }
                requiredFloor = mapKeyToFloor(key);
            }
            stoppedTime++;
            break;

        case GOING_DOWN_STATE:
            if (requiredFloor == actualFloor) {
                actualElevatorFsmState = STOPPED_STATE;
            } else if (key == MOTOR_KEY) {
                actualFloor--;
            }
            break;

        default:
            initElevatorFsm();
            break;
    }

    actualFloorLedIndicator(actualFloor);
    motorStateIndicator(actualElevatorFsmState);
    actualFloor = actualFloor % 3;
    return;
}

static bool_t isAcctionKey(gpioMap_t key) {
	return key == LOW_FLOOR_KEY || key == FIRST_FLOOR_KEY || key == SECOND_FLOOR_KEY;
}
