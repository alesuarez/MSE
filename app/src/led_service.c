#include "led_service.h"
#include "door_fsm.h"

#define DEFAULT_ON_TIME_LED 200

static void ledOneOn();
static void ledTwoOn();
static void ledThreeOn();
static void ledsOff();

static void rgbGreenLed();
static void rgbRedLedOn();
static void rgbRedLedOff();

void actualDoorLedIndicator(DoorFsmState doorState) {
	static bool_t ledOn = TRUE;
	static uint16_t ledOnTime = ZERO_TIME;

	switch(doorState){
		case OPENING_STATE:
			ledOneOn();
			break;
		case STOPPED_STATE:
			ledTwoOn();
			break;
		case CLOSING_STATE:
			ledThreeOn();
			break;
		case CLOSED_STATE:
			rgbGreenLed();
			break;
		default:
			ledsOff();
			break;
	}
	// todo: parpadeo RGB rojo
	return;
}

static void ledOneOn() {
	gpioWrite(LED1, TRUE);
	gpioWrite(LED2, FALSE);
	gpioWrite(LED3, FALSE);
	gpioWrite(LEDB, FALSE);
	gpioWrite(LEDG, FALSE);
}

static void ledTwoOn() {
	gpioWrite(LED1, FALSE);
	gpioWrite(LED2, TRUE);
	gpioWrite(LED3, FALSE);
	gpioWrite(LEDB, FALSE);
	gpioWrite(LEDG, FALSE);
}

static void ledThreeOn() {
	gpioWrite(LED1, FALSE);
	gpioWrite(LED2, FALSE);
	gpioWrite(LED3, TRUE);
	gpioWrite(LEDB, FALSE);
	gpioWrite(LEDG, FALSE);
}

static void ledsOff() {
	gpioWrite(LED1, FALSE);
	gpioWrite(LED2, FALSE);
	gpioWrite(LED3, FALSE);
	gpioWrite(LEDB, FALSE);
	gpioWrite(LEDG, FALSE);
}

static void rgbGreenLed() {
	gpioWrite(LED1, FALSE);
	gpioWrite(LED2, FALSE);
	gpioWrite(LED3, FALSE);
	gpioWrite(LEDB, FALSE);
	gpioWrite(LEDR, FALSE);
	gpioWrite(LEDG, TRUE);
}

void rgbRedStatus(DoorFsmState doorState) {
	static bool_t ledStatus = TRUE;
	if (doorState != CLOSED_STATE) {
		if(ledStatus) {
			rgbRedLedOn();
			ledStatus = FALSE;
		} else {
			rgbRedLedOff();
			ledStatus = TRUE;
		}
	}
}

static void rgbRedLedOn() {
	//gpioWrite(LEDB, FALSE);
	gpioWrite(LEDR, TRUE);
	//gpioWrite(LEDG, FALSE);
}

static void rgbRedLedOff() {
	//gpioWrite(LEDB, FALSE);
	gpioWrite(LEDR, FALSE);
	//gpioWrite(LEDG, FALSE);
}
