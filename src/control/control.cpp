#define CONTROL

#include "control/control.h"
#include "config.h"

void init_control() {
    driver = new MovementController(
        new Motor(Pins::DRIVER_0_A, Pins::DRIVER_0_B, Pins::DRIVER_0_PWM, 305), //M1 ALTO/SX
        new Motor(Pins::DRIVER_1_A, Pins::DRIVER_1_B, Pins::DRIVER_1_PWM, 55),  //M2 ALTO/DX
        new Motor(Pins::DRIVER_2_A, Pins::DRIVER_2_B, Pins::DRIVER_2_PWM, 135), //M3 BASSO/DX
        new Motor(Pins::DRIVER_3_A, Pins::DRIVER_3_B, Pins::DRIVER_3_PWM, 225)  //M4 BASSO/SX
    );
    position = new PositionController();
}

void update_control() {
    position->update();
}
