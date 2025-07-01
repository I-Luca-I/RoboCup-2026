#define SENSORS

#include "sensors/sensors.h"
#include "utility/filters.h"

void init_sensors() {
    compass = new BNO();
    lines = new Lines();
    ball = new Ball();
    attack_goal = new Goal();
    defence_goal = new Goal();
    ball_presence = new BallPresence();
}

void read_sensors() {
    compass->read(); // CAMBIA RESISTENZE SENSORE LINE 68 OHM
    lines->read();
    ball->read();
    
    readMV();
    attack_goal->update();
    // if (attack_goal->seen) {
    //     if (attack_goal->angle < 90) attack_goal->angle *= 1.5;
    //     attack_goal->angle = filter_angle(attack_goal->angle, attack_goal->p_angle, 0.1);
    //     attack_goal->p_angle = attack_goal->angle;
    // }

    defence_goal->update();
    // if (defence_goal->seen) {
    //     defence_goal->angle = filter_angle(defence_goal->angle, defence_goal->p_angle, 0.1);
    //     defence_goal->p_angle = defence_goal->angle;
    // }

    ball_presence->update();
}
