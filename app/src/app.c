/*============================================================================
 * Autor: Suarez, Sebastian Alejandro
 *===========================================================================*/

#include "app.h"
#include "debounce_fsm.h"
#include "elevator_fsm.h"
#include "key_service.h"
#include "sapi.h"

#define DEFAULT_BAUD_RATE 115200
#define DEFAULT_DEBOUNCE_TIME 40
#define DEFAULT_ELEVATOR_TIME 50

debounceData_t  lowLevelKey, floorOneKey, floorTwoKey, motorKey;
gpioMap_t pressedKey;

int main(void) {

    boardConfig();

    delay_t keysDelay;
    delay_t elevatorDelay;

    delayConfig(&keysDelay, DEFAULT_DEBOUNCE_TIME);
    delayConfig(&elevatorDelay, DEFAULT_ELEVATOR_TIME);

    uartConfig(UART_USB, DEFAULT_BAUD_RATE);

    initDebounceFsm(&lowLevelKey, LOW_FLOOR_KEY);
    initDebounceFsm(&floorOneKey, FIRST_FLOOR_KEY);
    initDebounceFsm(&floorTwoKey, SECOND_FLOOR_KEY);
    initDebounceFsm(&motorKey, MOTOR_KEY);

    initElevatorFsm();

    while (TRUE) {
        if (delayRead(&keysDelay)) {
            updateDebounceFsm(&lowLevelKey, &pressedKey);
            updateDebounceFsm(&floorOneKey, &pressedKey);
            updateDebounceFsm(&floorTwoKey, &pressedKey);
            updateDebounceFsm(&motorKey, &pressedKey);
        }

        if (delayRead(&elevatorDelay)) {
        	updateElevatorFsm(&pressedKey);
        }
    }
    return 0;
}

