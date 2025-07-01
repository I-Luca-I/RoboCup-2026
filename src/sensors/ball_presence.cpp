#include <Arduino.h>
#include "sensors/ball_presence.h"
#include "utility/filters.h"
#include "config.h"

BallPresence::BallPresence() {
}

void BallPresence::update() {
    #ifdef TEENSY_ENV
    value = analogRead(Pins::BALL_PRESENCE);
    #endif
    value = filter(value, p_value, 0.5);
    p_value = value;
    is_in_mouth = value < BALL_PRESENCE_THRESHOLD;
}
