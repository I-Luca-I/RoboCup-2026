#include "sensors/sensors.h"
#include "control/control.h"
#include "behavior/behavior.h"
#include "behavior/bounds.h"

void line_react(byte read_status, float mult) {
    #ifdef POLAR
    driver->speed = SPEED_LINE_REACT;
    driver->absolute = false;

    int dirX = 0;
    int dirY = 0;

    if (((read_status & 0b10000000) >> 7) == 1) dirX -= 100;
    if (((read_status & 0b01000000) >> 6) == 1) dirX -= 150;
    if (((read_status & 0b00100000) >> 5) == 1) dirY -= 100;
    if (((read_status & 0b00010000) >> 4) == 1) dirY -= 150;
    if (((read_status & 0b00001000) >> 3) == 1) dirX += 100;
    if (((read_status & 0b00000100) >> 2) == 1) dirX += 150;
    if (((read_status & 0b00000010) >> 1) == 1) dirY += 100;
    if (((read_status & 0b00000001) >> 0) == 1) dirY += 150;

    driver->dir = degrees(atan2((double)dirY, (double)dirX));
    #endif

    #ifdef CARTESIAN
    if (((read_status & 0b10000000) >> 7) == 1) driver->dx -= SPEED_LINE_REACT*mult;
    if (((read_status & 0b01000000) >> 6) == 1) driver->dx -= SPEED_LINE_REACT*mult;
    if (((read_status & 0b00100000) >> 5) == 1) driver->dy -= SPEED_LINE_REACT*mult;
    if (((read_status & 0b00010000) >> 4) == 1) driver->dy -= SPEED_LINE_REACT*mult;
    if (((read_status & 0b00001000) >> 3) == 1) driver->dx += SPEED_LINE_REACT*mult;
    if (((read_status & 0b00000100) >> 2) == 1) driver->dx += SPEED_LINE_REACT*mult;
    if (((read_status & 0b00000010) >> 1) == 1) driver->dy += SPEED_LINE_REACT*mult;
    if (((read_status & 0b00000001) >> 0) == 1) driver->dy += SPEED_LINE_REACT*mult;
    #endif
}

void stay_on_line(byte read_status, float mult) {
    static unsigned long start_time = 0; 
    static byte saved_status = 0;

    if (read_status != 0) {
        start_time = millis();
        saved_status = read_status;
    }

    if (millis() - start_time > 100) {
        saved_status = read_status;
    }

    if (((saved_status & 0b10000000) >> 7) == 1) driver->dx += GAME_SPEED*mult;
    if (((saved_status & 0b01000000) >> 6) == 1) driver->dx += GAME_SPEED*mult;
    if (((saved_status & 0b00001000) >> 3) == 1) driver->dx += GAME_SPEED*mult;
    if (((saved_status & 0b00000100) >> 2) == 1) driver->dx += GAME_SPEED*mult;

    if (((saved_status & 0b00100000) >> 5) == 1) driver->dy -= GAME_SPEED/2;
    if (((saved_status & 0b00010000) >> 4) == 1) driver->dy -= GAME_SPEED/2;
    if (((saved_status & 0b00000010) >> 1) == 1) driver->dy += GAME_SPEED/2;
    if (((saved_status & 0b00000001) >> 0) == 1) driver->dy += GAME_SPEED/2;

    if (defence_goal->angle < 180) {
        if (((saved_status & 0b00100000) >> 5) == 1) driver->dx += GAME_SPEED*mult;
        if (((saved_status & 0b00010000) >> 4) == 1) driver->dx += GAME_SPEED*mult;
        if (((saved_status & 0b00000010) >> 1) == 1) driver->dy += GAME_SPEED*mult;
        if (((saved_status & 0b00000001) >> 0) == 1) driver->dy += GAME_SPEED*mult;
    } else {
        if (((saved_status & 0b00100000) >> 5) == 1) driver->dy -= GAME_SPEED*mult;
        if (((saved_status & 0b00010000) >> 4) == 1) driver->dy -= GAME_SPEED*mult;
        if (((saved_status & 0b00000010) >> 1) == 1) driver->dx += GAME_SPEED*mult;
        if (((saved_status & 0b00000001) >> 0) == 1) driver->dx += GAME_SPEED*mult;
    }
}

bool goto_center() {
    driver->speed = SPEED_LINE_REACT;
    driver->absolute = false;

    if (position->set) driver->dir = (int)(270 - degrees(atan2(position->coord.y, position->coord.x))) % 360;
    else if (attack_goal->seen and defence_goal->seen) driver->dir = (attack_goal->angle + defence_goal->angle)/2;
    else if (attack_goal->seen and !defence_goal->seen) driver->dir = (attack_goal->angle < 180) ? 90 : 270;
    else if (!attack_goal->seen and defence_goal->seen) driver->dir = (defence_goal->angle < 180) ? 90 : 270;
    else return false;
    return true;
}
