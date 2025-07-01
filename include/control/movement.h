#pragma once
#include <PID_v1.h>
#include <Arduino.h>
#include "actuators/motors.h"

#define KP 0.8
#define KI 0.1
#define KD 0.05

class MovementController {
private:
    double input{0}, output{0}, setPoint{0};
    PID* pid; 

public:
    //motors[0]: M1 ALTO-SX
    //motors[1]: M2 ALTO-DX
    //motors[2]: M3 BASSO-DX
    //motors[3]: M4 BASSO-SX
    Motor* motors[4];

    int dir{0}; // The direction the robot will move at (can be used in conjunction with dx/dy)
    int speed{0}; // The speed the robot will move at (can be used in conjunction with dx/dy)
    int orient{0}; // The direction the robot will look at while moving, in degrees
    int dx{0}; // The forward/backward movement of the robot (can be used in conjunction with dir)
    int dy{0}; // The right/left movement of the robot (can be used in conjunction with dir)
    bool brake{false}; // If true, the robot will stop all the motors instead of moving
    bool absolute{false}; // If true, the direction of the robot will be absolute, it won't be affected by its angle
    int pid_limit{255}; // The limits imposed to the PID (it SHOULD affect how quickly it applies)

    MovementController(Motor* m0, Motor* m1, Motor* m2, Motor* m3);
    void move();
    void stop();
    void test(int test);
};
