#include "led_service.h"
#include "elevator_fsm.h"

#define RED_LED 	LED1
#define YELLOW_LED 	LED2
#define GREEN_LED 	LED3

static void redOn();
static void redOff();
static void greenOn();
static void yellowOn();
static void redYellowOn();
static void rgbBlueLed();
static void rgbRedLed();
static void rgbGreenLed();
static void error();

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
			error();
			break;
	}
	return;
}

void motorStateIndicator(ElevatorFsmState elevatorFsmState) {
	switch(elevatorFsmState){
		case LOW_FLOOR_STATE:
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

static void redOn() {
	gpioWrite(RED_LED, TRUE);
	gpioWrite(YELLOW_LED, FALSE);
	gpioWrite(GREEN_LED, FALSE);
}

static void redOff() {
	gpioWrite(RED_LED, FALSE);
}

static void greenOn() {
	gpioWrite(RED_LED, FALSE);
	gpioWrite(YELLOW_LED, FALSE);
	gpioWrite(GREEN_LED, TRUE);
}

static void yellowOn() {
	gpioWrite(RED_LED, FALSE);
	gpioWrite(YELLOW_LED, TRUE);
	gpioWrite(GREEN_LED, FALSE);
}

static void redYellowOn() {
	gpioWrite(RED_LED, TRUE);
	gpioWrite(YELLOW_LED, TRUE);
	gpioWrite(GREEN_LED, FALSE);
}

static void rgbBlueLed() {
	gpioWrite(LEDB, TRUE);
	gpioWrite(LEDR, FALSE);
	gpioWrite(LEDG, FALSE);
}

static void rgbRedLed() {
	gpioWrite(LEDB, FALSE);
	gpioWrite(LEDR, TRUE);
	gpioWrite(LEDG, FALSE);
}

static void rgbGreenLed() {
	gpioWrite(LEDB, FALSE);
	gpioWrite(LEDR, FALSE);
	gpioWrite(LEDG, TRUE);
}

static void error() {
	gpioWrite(RED_LED, TRUE);
	gpioWrite(YELLOW_LED, TRUE);
	gpioWrite(GREEN_LED, TRUE);
	gpioWrite(LEDG, TRUE);
}
