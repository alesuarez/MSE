/*============================================================================
 * Autor: Suarez, Sebastian Alejandro
 *===========================================================================*/

#include "app.h"
#include "debounce_fsm.h"
#include "key_service.h"
#include "sapi.h"

#define DEFAULT_BAUD_RATE 115200
#define DEFAULT_DEBOUNCE_TIME 40

debounceData_t  lowLevelKey, floorOneKey, floorTwoKey;

int main(void) {

    boardConfig();

    delay_t keysDelay;

    delayConfig(&keysDelay, DEFAULT_DEBOUNCE_TIME);

    uartConfig(UART_USB, DEFAULT_BAUD_RATE);

    initDebounceFsm(&lowLevelKey, LOW_LEVEL);
    initDebounceFsm(&floorOneKey, FIRST_FLOOR);
    initDebounceFsm(&floorTwoKey, SECOND_FLOOR);

    while (TRUE) {
        if (delayRead(&keysDelay)) {
            updateDebounceFsm(&lowLevelKey);
            updateDebounceFsm(&floorOneKey);
            updateDebounceFsm(&floorTwoKey);
        }
    }
    return 0;
}

