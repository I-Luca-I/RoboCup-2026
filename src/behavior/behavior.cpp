#include <Arduino.h>
#include "control/control.h"
#include "behavior/behavior.h"
#include "behavior/striker.h"
#include "behavior/keeper.h"

void behavior() {
    driver->dir = 0;
    driver->dx = 0;
    driver->dy = 0;
    driver->speed = 0;
    driver->orient = 0;
    driver->brake = false;
    driver->absolute = false;
    driver->pid_limit = 255;

    #ifdef STRIKER
    striker();
    #endif

    #ifdef KEEPER
    keeper();
    driver->orient = 0;
    #endif
}