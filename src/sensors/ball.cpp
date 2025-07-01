#include <Arduino.h>
#include "sensors/sensors.h"
#include "sensors/ball.h"
#include "control/control.h"
#include "utility/filters.h"
#include "config.h"

Ball::Ball() {
    #ifdef BLUEPILL_ENV
    BallSerial = new HardwareSerial(Pins::ESP32_RX, Pins::ESP32_TX);
    BallSerial->begin(57600);
    #endif

    #ifdef TEENSY_ENV
    ATMEGA_SERIAL.begin(57600);
    #endif
}

void Ball::read() {
    #ifdef BLUEPILL_ENV
    while (BallSerial->available()) {
        String message = BallSerial->readStringUntil('b'); 
        relative_angle = message.substring(message.lastIndexOf("B")+1, message.indexOf("-")).toInt();
        distance = message.substring(message.lastIndexOf("-")+1).toInt();
    }
    #endif

    #ifdef TEENSY_ENV
    while (ATMEGA_SERIAL.available()) {
        String message = ATMEGA_SERIAL.readStringUntil('b'); 
        relative_angle = message.substring(message.lastIndexOf("B")+1, message.indexOf("-")).toInt();
        distance = message.substring(message.lastIndexOf("-")+1).toInt();
    }
    #endif

    relative_angle = filter_angle(relative_angle, p_angle, 0.45);
    p_angle = relative_angle;

    absolute_angle = (int)(relative_angle + compass->angle) % 360;

    distance = filter(distance, p_distance, 0.5);
    p_distance = distance;

    seen = distance > 0;
}

void Ball::test() {
    driver->dir = absolute_angle;
    driver->speed = 50;
    driver->dx = 0;
    driver->dy = 0;
    driver->orient = 0;
}