#include "key_service.h"
#include "led_service.h"

bool_t isPress(gpioMap_t key) {
	return !gpioRead(key);
}

bool_t notPress(gpioMap_t key) {
	return gpioRead(key);
}

// down flag
bool_t buttonPressed(gpioMap_t key) {
	return key == TEC1 || key == TEC3;
}

// up flag
bool_t buttonReleased(gpioMap_t key) {
	return key == TEC2 || key ==  TEC4;
}
