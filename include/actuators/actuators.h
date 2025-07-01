#pragma once

#include "actuators/kicker.h"
#include "actuators/roller.h"

#ifdef ACTUATORS
#define a_extr
#else
#define a_extr extern
#endif

a_extr Kicker* kicker;
a_extr Roller* roller;

void init_actuators();
void update_actuators();
