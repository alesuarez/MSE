#include "../inc/traffic_light_fsm.h"
#include "led_service.h"


#define RED_EXPIRATION_TIME 20
#define RED_YELLOW_EXPIRATION_TIME 25
#define GREEN_EXPIRATION_TIME 55
#define YELLOW_EXPIRATION_TIME 60

typedef enum {
	RED_STATE,
	RED_YELLOW_STATE,
	YELLOW_STATE,
	GREEN_STATE
} mefState;

mefState actualState;

void initMEF() {
	actualState = RED_STATE;
}

void updateMEF(tick_t timeCount) {

	switch (actualState) {
	case RED_STATE:
		redOn();
		if (timeCount == RED_EXPIRATION_TIME) {
			actualState = RED_YELLOW_STATE;
		}
		break;
	case RED_YELLOW_STATE:
		redYellowOn();
		if (timeCount == RED_YELLOW_EXPIRATION_TIME) {
			actualState = GREEN_STATE;
		}
		break;
	case GREEN_STATE:
		greenOn();
		if (timeCount == GREEN_EXPIRATION_TIME) {
			actualState = YELLOW_STATE;
		}
		break;
	case YELLOW_STATE:
		yellowOn();
		if (timeCount == YELLOW_EXPIRATION_TIME) {
			actualState = RED_STATE;
		}
		break;
	default:
		initMEF();
		break;
	}
}


