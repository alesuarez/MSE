#include "elevator_fsm.h"

#define DEFAULT_MAX_STOPPED_TIME_SEG 10000
#define ZERO 0

ElevatorFsmState actualElevatorFsmState;

void initElevatorFsm() {
    actualElevatorFsmState = LOW_FLOOR_STATE;
}

void updateElevatorFsm(Action action, uint16_t floor, Key key) {
    static uint16_t actualFloor = LOW_FLOOR;
    static uint16_t requiredFloor = LOW_FLOOR;
    static uint16_t stoppedTime = ZERO;

    switch (actualElevatorFsmState) {

        case LOW_FLOOR_STATE:
            if (acction == GOING_UP) {
                requiredFloor = floor;
                actualElevatorFsmState = GOING_UP_STATE;
            }
            break;

        case GOING_UP_STATE:
            if (requiredFloor == actualFloor) {
                actualElevatorFsmState = STOPPED_STATE;
            } else if (Key == MOTOR_KEY) {
                actualFloor++;
            }
            break;

        case STOPPED_STATE:
            if (stoppedTime >= DEFAULT_MAX_STOPPED_TIME_SEG) {
                requiredFloor = LOW_FLOOR;
                stoppedTime = ZERO;
            } else if (key == LOW_FLOOR_KEY || key == FIRST_FLOOR_KEY || key == SECOND_FLOOR_KEY ){
                if (actualFloor - requiredFloor > ZERO) {
                    actualElevatorFsmState = GOING_DOWN_STATE;
                } else {
                    actualElevatorFsmState = GOING_UP_STATE;
                }
                requiredFloor = floor;
            }
            stoppedTime++;
            break;

        case GOING_DOWN_STATE:
            if (requiredFloor == actualFloor) {
                actualElevatorFsmState = STOPPED_STATE;
            } else if (Key == MOTOR_KEY) {
                actualFloor--;
            }
            break;

        default:
            initElevatorFsm();
            break;
    }

    actualFloorLedIndicator(actualFloor);

    return;
}