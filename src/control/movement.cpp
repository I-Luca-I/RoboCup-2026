#include "sensors/sensors.h"
#include "control/control.h"
#include "control/movement.h"

MovementController::MovementController(Motor* m0, Motor* m1, Motor* m2, Motor* m3) {
    // Motors init
    motors[0] = m0;
    motors[1] = m1;
    motors[2] = m2;
    motors[3] = m3;

    // PID init
    pid = new PID(&input, &output, &setPoint, KP, KI, KD, DIRECT);
    pid->SetSampleTime(2);
    pid->SetMode(AUTOMATIC);
    pid->SetControllerDirection(DIRECT);
    pid->setAngleWrap(true);
}

void MovementController::move() {
    // Motor movement
    double r_dir = radians(dir);
    float dirX = speed * cos(r_dir) + dx;
    float dirY = -(speed * sin(r_dir) + dy);

    this->dx = 0;
    this->dy = 0;

    float motorSpeed[4];
    double orient_mot = (absolute) ? compass->angle : 0;
    motorSpeed[0] = (dirX * sin(radians(motors[0]->ANGLE + orient_mot))) + (dirY * cos(radians(motors[0]->ANGLE + orient_mot)));
    motorSpeed[1] = (dirX * sin(radians(motors[1]->ANGLE + orient_mot))) + (dirY * cos(radians(motors[1]->ANGLE + orient_mot)));
    motorSpeed[2] = (dirX * sin(radians(motors[2]->ANGLE + orient_mot))) + (dirY * cos(radians(motors[2]->ANGLE + orient_mot)));
    motorSpeed[3] = (dirX * sin(radians(motors[3]->ANGLE + orient_mot))) + (dirY * cos(radians(motors[3]->ANGLE + orient_mot)));

    // PID
    pid->SetOutputLimits(-pid_limit, pid_limit);
    input = (compass->angle > 180) ? compass->angle - 360.0 : compass->angle;
    setPoint = (orient > 180) ? orient - 360.0 : orient;

    static double offsetPid = 0;
    if(pid->Compute()) offsetPid = -output;
    
    motorSpeed[0] += offsetPid;
    motorSpeed[1] += offsetPid;
    motorSpeed[2] += offsetPid;
    motorSpeed[3] += offsetPid;

    motorSpeed[0] = constrain(motorSpeed[0], -255, 255);
    motorSpeed[1] = constrain(motorSpeed[1], -255, 255);
    motorSpeed[2] = constrain(motorSpeed[2], -255, 255);
    motorSpeed[3] = constrain(motorSpeed[3], -255, 255);

    // Drive motors
    motors[0]->drive(motorSpeed[0]);
    motors[1]->drive(motorSpeed[1]);
    motors[2]->drive(motorSpeed[2]);
    motors[3]->drive(motorSpeed[3]);

    if (brake) stop();
}

void MovementController::stop() {
    motors[0]->stop();
    motors[1]->stop();
    motors[2]->stop();
    motors[3]->stop();
}

void MovementController::test(int test) {
    switch (test) {
    case 0: // MOTORS
        motors[0]->test();
        motors[1]->test();
        motors[2]->test();
        motors[3]->test();
        break;

    case 1: // PID
        speed = 0;
        dx = 0;
        dy = 0;
        orient = 0;
        move();
        break;

    case 2: // POLAR MOVEMENT (should move 45°)
        speed = 50;
        dir = 45;
        dx = 0;
        dy = 0;
        orient = 0;
        move();
        break;

    case 3: // CARDINAL MOVEMENT (should move 45°)
        speed = 0;
        dx = 50;
        dy = 50;
        orient = 0;
        move();
        break;

    case 4: // MIXED MOVEMET (should move 45°)
        speed = 50;
        dir = 0;
        dx = 0;
        dy = 50;
        orient = 0;
        move();
        break;
    
    default:
        break;
    }
}
