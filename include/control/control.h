#pragma once

#include "control/movement.h"
#include "control/position.h"

#ifdef CONTROL
#define c_extr
#else
#define c_extr extern
#endif

c_extr MovementController* driver;
c_extr PositionController* position;

void init_control();
void update_control();
