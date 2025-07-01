#include <Arduino.h>
#include "sensors/sensors.h"
#include "control/control.h"
#include "behavior/bounds.h"
#include "behavior/behavior.h"
#include "behavior/keeper.h"

void keeper() {
    static unsigned long start_time, start_defend_time = 0;
    static byte game_state = RESET;

    switch (game_state) {
    case RESET:
        if (((lines->status & 0b00001100) >> 2) > 0) {
            game_state = DEFEND;
            start_time = millis();
        } else {
            goto_goal();
            defend();
            stay_on_line(lines->status);
        }
        break;

    case DEFEND:
        if (ball->seen and ((is_ball_close(ball->distance) and (ball->absolute_angle < 30 or ball->absolute_angle > 330)) or ball_presence->is_in_mouth)) {
            game_state = PARRY;
            start_time = millis();
        } else if (millis() - start_time >= IDLE_TIME) {
            game_state = RESET;
        } else {
            if (lines->status) start_time = millis();
            defend();
            stay_on_line(lines->status);
        }
        break;

    case PARRY:
        if (
            !is_ball_close(ball->distance) or // Ball far
            millis() - start_time >= SAVE_TIME or // Enough time passed
            (ball->absolute_angle > 90 and ball->absolute_angle < 270) or // Ball behind
            (millis() - start_time >= 100 and lines->status) // Seen lines after 100ms
        ) {
            game_state = RESET;
        } else {
            save();
            stay_on_line(lines->status);
        }
        break;
    
    default:
        break;
    }

    driver->dx *= 0.6;
    driver->orient = 0;
}

void goto_goal() {
    driver->orient = 0;
    driver->dir = 180;
    driver->speed = SETUP_SPEED;
}

void defend() {
    // driver->orient = (defence_goal->angle + 180) % 360;
    // driver->orient = (ball->seen) ? ball->absolute_angle : 0;
    driver->orient = 0;
    driver->absolute = true;

    // if (ball->absolute_angle < 45)  driver->dy += map(ball->absolute_angle, 0, 45, GAME_SPEED, GAME_SPEED*1.5);
    // else if (ball->absolute_angle < 135) driver->dy += map(ball->absolute_angle, 45, 135, GAME_SPEED*1.5, GAME_SPEED/1.5);
    // else if (ball->absolute_angle > 315) driver->dy -= map(ball->absolute_angle, 315, 360, GAME_SPEED*1.5, GAME_SPEED);
    // else if (ball->absolute_angle > 225) driver->dy -= map(ball->absolute_angle, 225, 315, GAME_SPEED/1.5, GAME_SPEED*1.5);

    if (ball->absolute_angle < 135) driver->dy += map(ball->absolute_angle, 0, 135, GAME_SPEED*0.8, GAME_SPEED*1.5);
    if (ball->absolute_angle > 225) driver->dy -= map(ball->absolute_angle, 225, 360, GAME_SPEED*1.5, GAME_SPEED*0.8);

    if (!ball->seen) driver->dy = 0;

    // if(defence_goal->angle < 180) driver->dy += map(defence_goal->angle, 90, 180, GAME_SPEED, GAME_SPEED/5);
	// if(defence_goal->angle > 180) driver->dy -= map(defence_goal->angle, 180, 270, GAME_SPEED/5, GAME_SPEED);

    // if (is_goal_visible(defence_goal->area)) {
    //     if (defence_goal->angle < 180) driver->dy += GAME_SPEED;
    //     if (defence_goal->angle > 180) driver->dy -= GAME_SPEED;
    // }
}

void save() {
    driver->speed = GAME_SPEED;
    driver->orient = 0;

    if      (ball->absolute_angle < 90)  driver->dir = ball->absolute_angle * 1.5;
    else if (ball->absolute_angle > 270) driver->dir = (360 - ((360 - ball->relative_angle) * 1.5));
    else driver->speed = 0;
}
