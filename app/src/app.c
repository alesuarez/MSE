/*============================================================================
 * Autor: Suarez, Sebastian Alejandro
 * Licencia:
 * Fecha:
 *===========================================================================*/
#include "app.h"
#include "debounce_fsm.h"
#include "sapi.h"

debounceData_t keyOne, keyTwo;

int main(void) {

	boardConfig();

	delay_t keyDelay;

	delayConfig(&keyDelay, 40);

	uartConfig(UART_USB, 115200);

	initDebounceFsm(&keyOne, TEC1);
	initDebounceFsm(&keyTwo, TEC2);

	while (TRUE) {
		if(delayRead(&keyDelay)) {
			updateDebounceFsm(&keyOne);
			updateDebounceFsm(&keyTwo);
		}
	}
	return 0;
}

