#include "key_service.h"
#include "led_service.h"

bool_t isPress(gpioMap_t key) {
	return !gpioRead(key);
}

bool_t notPress(gpioMap_t key) {
	return gpioRead(key);
}

// down flag
void buttonPressed(gpioMap_t key) {
	switch(key){
	case TEC1:
		redOn();
		break;
	case TEC2:
		redOff();
		break;
	default:
		break;
	}
	return;
}

// up flag
void buttonReleased(gpioMap_t key) {
	switch(key){
	case TEC1:
		break;
	case TEC2:
		break;
	default:
		break;
	}
	return;
}
