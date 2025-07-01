#define ACTUATORS

#include "actuators/actuators.h"

void init_actuators() {
    kicker = new Kicker();
    roller = new Roller();
}

void update_actuators() {
    kicker->update();
}
