/*============================================================================
 * Autor: Suarez, Sebastian Alejandro
 *===========================================================================*/

#include "app.h"
#include "debounce_fsm.h"
#include "door_fsm.h"
#include "key_service.h"
#include "led_service.h"
#include "sapi.h"

#define DEFAULT_BAUD_RATE 115200
#define DEFAULT_DEBOUNCE_TIME 40
#define DEFAULT_DOOR_TIME 200
#define DEFAULT_RGB_RED_TIME 500

debounceData_t  tec1Key, tec2Key, tec3Key, tec4Key;
gpioMap_t pressedKey;

int main(void) {

    boardConfig();

    delay_t keysDelay;
    delay_t doorDelay;
    delay_t rgbDelay;

    delayConfig(&keysDelay, DEFAULT_DEBOUNCE_TIME);
    delayConfig(&doorDelay, DEFAULT_DOOR_TIME);
    delayConfig(&rgbDelay, DEFAULT_RGB_RED_TIME);

    uartConfig(UART_USB, DEFAULT_BAUD_RATE);

    initDebounceFsm(&tec1Key, TEC1);
    initDebounceFsm(&tec2Key, TEC2);
    initDebounceFsm(&tec3Key, TEC3);
    initDebounceFsm(&tec4Key, TEC4);

    initDoorFsm();

    while (TRUE) {
        if (delayRead(&keysDelay)) {
            updateDebounceFsm(&tec1Key, &pressedKey);
            updateDebounceFsm(&tec2Key, &pressedKey);
            updateDebounceFsm(&tec3Key, &pressedKey);
            updateDebounceFsm(&tec4Key, &pressedKey);
        }

        if (delayRead(&doorDelay)) {
        	updateDoorFsm(&pressedKey);
        }

        if (delayRead(&rgbDelay)) {
        	updateRgbLedDoor();
        }
    }
    return 0;
}

