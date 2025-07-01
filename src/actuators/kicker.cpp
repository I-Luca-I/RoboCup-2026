#include <Arduino.h>
#include "sensors/sensors.h"
#include "actuators/kicker.h"
#include "config.h"

Kicker::Kicker() {
    pinMode(Pins::KICKER, OUTPUT);
}

void Kicker::kick() {    
    if (millis() - t_charge >= KICKER_CHARGE_TIME and digitalRead(Pins::KICKER) == LOW) {
        digitalWrite(Pins::KICKER, HIGH);
        t_atk = millis();
    } 
}

void Kicker::update() {
    if (millis() - t_atk >= KICKER_ATK_TIME and digitalRead(Pins::KICKER) == HIGH) {
        digitalWrite(Pins::KICKER, LOW); 
        t_charge = millis();
    } 
}

void Kicker::test() {
    digitalWrite(Pins::KICKER, HIGH);
    delay(1000);
    digitalWrite(Pins::KICKER, LOW);
    delay(1000);
}
