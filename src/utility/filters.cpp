#include <Arduino.h>
#include "utility/filters.h"

int filter(float valA, float valP, float k) { //0<k<1
	int val0 = (k * valA) + ((1 - k) * valP);
	return val0;
}

int filter_angle(float angleA, float angleP, float k) { //0<k<1
	float angle_cos = (k * cos(radians(angleA))) + ((1 - k) * cos(radians(angleP)));
	float angle_sin = (k * sin(radians(angleA))) + ((1 - k) * sin(radians(angleP)));
	int val0 = degrees(atan2(angle_sin, angle_cos));
	if (val0 < 0) val0 += 360;
	return val0;
}
