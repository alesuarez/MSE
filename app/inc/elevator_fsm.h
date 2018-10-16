#ifndef APP_INC_ELEVATOR_FSM_H
#define APP_INC_ELEVATOR_FSM_H

#define LOW_FLOOR       0
#define FIRST_FLOOR     1
#define SECOND_FLOOR    2


typedef enum {
    FIRST_FLOOR_STATE,
    GOING_UP_STATE,
    STOPPED_STATE,
    GOING_DOWN_STATE
} ElevatorFsmState;

#endif
