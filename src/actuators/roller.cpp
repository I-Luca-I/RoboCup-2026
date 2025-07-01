#include <Servo.h>
#include "actuators/roller.h"
#include "config.h"

Roller::Roller() {
    servo.attach(Pins::ROLLER);
    servo.writeMicroseconds(1000);
	delay(2000); 
}

void Roller::on() {
    static unsigned long t = 0;
    if (microseconds >= 1800) return; // SPEED: 1600-1800

    if (millis() - t >= 15) {
		servo.writeMicroseconds(microseconds);
        microseconds += 10;
        t = millis();
    }
}

void Roller::off() {
    servo.writeMicroseconds(1200);
    microseconds = 1200;
}

void Roller::test() {
    static unsigned long t = 0;

    if (millis() - t < 5000) {
        on();
    } else if (millis() - t < 10000) {
        off();
    } else {
        t = millis();
    }
}
