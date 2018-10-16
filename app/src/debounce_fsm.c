#include "debounce_fsm.h"
#include "key_service.h"
#include "led_service.h"

#define DEBOUNCE_DEFAULT_TIME 40

void initDebounceFsm(debounceData_t * dataStruct, gpioMap_t key) {
	dataStruct->key = key;
	dataStruct->state = BUTTON_UP_STATE;
	return;
}

void updateDebounceFsm(debounceData_t * ptrDataStruct) {

	switch (ptrDataStruct->state) {

	case BUTTON_UP_STATE:
		if (isPress(ptrDataStruct->key)) {
			ptrDataStruct->state = BUTTON_FALLING_STATE;
		}
		break;

	case BUTTON_FALLING_STATE:
		if (isPress(ptrDataStruct->key)) {
				buttonPressed(ptrDataStruct->key);
				ptrDataStruct->state = BUTTON_DOWN_STATE;
			} else {
				ptrDataStruct->state = BUTTON_UP_STATE;
			}
		break;

	case BUTTON_DOWN_STATE:
		if (notPress(ptrDataStruct->key)) {
			ptrDataStruct->state = BUTTON_RISING_STATE;
		}
		break;

	case BUTTON_RISING_STATE:
		if (notPress(ptrDataStruct->key)) {
				buttonReleased(ptrDataStruct->key);
				ptrDataStruct->state = BUTTON_UP_STATE;
			} else {
				ptrDataStruct->state = BUTTON_DOWN_STATE;
			}
		break;

	default:
		ptrDataStruct->state = BUTTON_UP_STATE;
		break;
	}
	return;
}
