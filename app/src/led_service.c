#include "led_service.h"
#include "elevator_fsm.h"

#define RED_LED LED1
#define YELLOW_LED LED2
#define GREEN_LED LED3

void actualFloorLedIndicator(uint16_t floor) {
	switch(floor){
		case LOW_FLOOR:
			redOn();
			break;
		case FIRST_FLOOR:
			yellowOn();
			break;
		case SECOND_FLOOR:
			greenOn();
			break;
		default:
			error()
			break;
	}
	return;
}

void motorStateIndicator(ElevatorFsmState elevatorFsmState) {
	switch(elevatorFsmState){
		case FIRST_FLOOR_STATE:
			rgbBlueLed();
			break;
		case GOING_UP_STATE:
			rgbGreenLed();
			break;
		case STOPPED_STATE:
			rgbBlueLed();
			break;
		case GOING_DOWN_STATE:
			rgbRedLed();
			break;
		default:
			error();
			break;
	}
	return;
}

void redOn() {
	gpioWrite(RED_LED, TRUE);
	gpioWrite(YELLOW_LED, FALSE);
	gpioWrite(GREEN_LED, FALSE);
}

void redOff() {
	gpioWrite(RED_LED, FALSE);
}

void greenOn() {
	gpioWrite(RED_LED, FALSE);
	gpioWrite(YELLOW_LED, FALSE);
	gpioWrite(GREEN_LED, TRUE);
}

void yellowOn() {
	gpioWrite(RED_LED, FALSE);
	gpioWrite(YELLOW_LED, TRUE);
	gpioWrite(GREEN_LED, FALSE);
}

void redYellowOn() {
	gpioWrite(RED_LED, TRUE);
	gpioWrite(YELLOW_LED, TRUE);
	gpioWrite(GREEN_LED, FALSE);
}

void rgbBlueLed() {
	gpioWrite(LEDB, TRUE);
}

void rgbRedLed() {
	gpioWrite(LEDR, TRUE);
}

void rgbGreenLed() {
	gpioWrite(LEDG, TRUE);
}

void error() {
	gpioWrite(RED_LED, TRUE);
	gpioWrite(YELLOW_LED, TRUE);
	gpioWrite(GREEN_LED, TRUE);
	gpioWrite(LEDG, TRUE);
}
