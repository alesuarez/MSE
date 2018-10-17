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
	return key == LOW_FLOOR_KEY || key == FIRST_FLOOR_KEY || key == SECOND_FLOOR_KEY;
}

// up flag
bool_t buttonReleased(gpioMap_t key) {
	return key == MOTOR_KEY ? TRUE : FALSE;
}

uint16_t mapKeyToFloor(gpioMap_t key) {
	if (key == LOW_FLOOR_KEY) {
		return LOW_FLOOR;
	} else if (key == FIRST_FLOOR_KEY) {
		return FIRST_FLOOR;
	} else if (key == SECOND_FLOOR_KEY) {
		return SECOND_FLOOR;
	}
}
