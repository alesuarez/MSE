#include "door_fsm.h"
#include "led_service.h"
#include "uart_service.h"

#define DEFAULT_OPENING_CLOSING_TIME 50
#define BASE_TIME 2

DoorFsmState actualDoorFsmState;

void initDoorFsm() {
	actualDoorFsmState = CLOSED_STATE;
}

void updateDoorFsm(gpioMap_t * key) {
	static uint16_t openingTime = ZERO_TIME;
	static uint16_t closingTime = ZERO_TIME;

	switch (actualDoorFsmState) {

	case CLOSED_STATE:
		if (*key == TEC2) {
			actualDoorFsmState = OPENING_STATE;
			openingTime = ZERO_TIME;
		}
		break;

	case OPENING_STATE:
		if (*key == TEC3) {
			actualDoorFsmState = STOPPED_STATE;
		} else if (openingTime >= DEFAULT_OPENING_CLOSING_TIME) {
			actualDoorFsmState = OPEN_STATE;
		}
		printOpeningStatus(openingTime * BASE_TIME);
		openingTime++;
		break;

	case OPEN_STATE:
		if (*key == TEC4) {
			actualDoorFsmState = CLOSING_STATE;
			closingTime = ZERO_TIME;
		}
		break;

	case CLOSING_STATE:
		if (*key == TEC3 || *key == TEC1) {
			actualDoorFsmState = STOPPED_STATE;
			openingTime = DEFAULT_OPENING_CLOSING_TIME - closingTime;
		} else if (closingTime >= DEFAULT_OPENING_CLOSING_TIME) {
			actualDoorFsmState = CLOSED_STATE;
		}
		printClosingStatus(closingTime * BASE_TIME);
		closingTime++;
		break;

	case STOPPED_STATE:
		if (*key == TEC2) {
			actualDoorFsmState = OPENING_STATE;


		} else if (*key == TEC4) {
			closingTime = DEFAULT_OPENING_CLOSING_TIME - openingTime;
			actualDoorFsmState = CLOSING_STATE;
		}
		break;

	default:
		initDoorFsm();
		break;
	}

	actualDoorLedIndicator(actualDoorFsmState);
	*key = T_FIL1;

	return;
}

void updateRgbLedDoor() {
	rgbRedStatus(actualDoorFsmState);
}
