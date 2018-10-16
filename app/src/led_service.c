#include "led_service.h"

#define RED_LED LED1
#define YELLOW_LED LED2
#define GREEN_LED LED3

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
