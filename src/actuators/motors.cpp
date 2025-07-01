#include "actuators/motors.h"
#include <Arduino.h>

Motor::Motor(int a, int b, int pwm, int ANGLE){
    this->PIN_A = a;
    this->PIN_B = b;
    this->PIN_PWM = pwm;
    this->ANGLE = ANGLE;

    ANGLE_SIN = sin(radians(ANGLE));
    ANGLE_COS = cos(radians(ANGLE));

    pinMode(PIN_A, OUTPUT);
    pinMode(PIN_B, OUTPUT);
    pinMode(PIN_PWM, OUTPUT);
}

Motor::Motor() {}

void Motor::drive(int speed){
    if(speed > 0) {
        digitalWrite(PIN_A, LOW);
        digitalWrite(PIN_B, HIGH);

    }else if(speed < 0) {
        digitalWrite(PIN_A, HIGH);
        digitalWrite(PIN_B, LOW);
        speed *= -1;

    } else {
        digitalWrite(PIN_A, LOW);
        digitalWrite(PIN_B, LOW);
    }

    analogWrite(PIN_PWM, speed);
}

void Motor::stop(){
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
}

void Motor::test(){
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    analogWrite(PIN_PWM, 255);
    delay(1500);

    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    analogWrite(PIN_PWM, 0);
    delay(500);

    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    analogWrite(PIN_PWM, 255);
    delay(1500);

    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    analogWrite(PIN_PWM, 0);
    delay(500);
}
