#include "sensors/sensors.h"
#include "actuators/actuators.h"
#include "control/control.h"
#include "behavior/behavior.h"
#include "behavior/striker.h"
#include "behavior/bounds.h"
#include "config.h"

#define is_line_NS(status) (((status & 0b11000000) >> 6) or ((status & 0b00001100) >> 2))
#define is_line_EW(status) (((status & 0b00110000) >> 4) or ((status & 0b00000011) >> 0))

void striker() {
    static unsigned long start_time;
    static byte game_state = PLAY, saved_status;
    
    switch (game_state) {
    case PLAY:
        if (lines->status) {
            saved_status = lines->status;
            game_state = STOP;
            start_time = millis();
        } else {
            attack();
        }
        break;

    case STOP:
        if (millis() - start_time >= STOP_TIME) {
            game_state = LINE_REACT;
            start_time = millis();
        } else {
            driver->brake = true;
        }
        break;

    case LINE_REACT:
        if (millis() - start_time >= LINE_REACT_TIME) {
            if (lines->status) {
                saved_status = lines->status;
                start_time = millis();
            } else {
                game_state = PLAY;
                driver->dx = 0;
                driver->dy = 0;
            }
        } else {
            // if (!goto_center()) line_react(saved_status);
            line_react(saved_status);
        }
        break;
    
    default:
        break;
    }
}

void attack() {
    #ifdef ROLLER
    static unsigned long start_time = -100;
    if (ball_presence->is_in_mouth) start_time = millis(); 
    if (millis() - start_time >= 100) { // BALL ISN'T IN MOUTH
        // DIRECTION & SPEED
        driver->speed = GAME_SPEED;
        if (ball->relative_angle < 90 or ball->relative_angle > 270) {
            if (ball->relative_angle < 90) driver->dir = ball->relative_angle * 0.75;
            if (ball->relative_angle > 270) driver->dir = 360 - ((360 - ball->relative_angle) * 0.75);
        }

        // else if (ball->relative_angle < 90)  driver->dir = ball->relative_angle * 2.2;
        // else if (ball->relative_angle > 270) driver->dir = 360 - ((360 - ball->relative_angle) * 2.5);

        else if (ball->relative_angle < 160) driver->dir = 160;
        else if (ball->relative_angle > 200) driver->dir = 200;

        else {
            if (!attack_goal->seen) driver->dir = 130;
            else driver->dir = (attack_goal->angle < 180) ? 130 : 230;
        }

        // ORIENT
        if (ball->relative_angle < 90 or ball->relative_angle > 270) driver->orient = ball->absolute_angle;
        else driver->orient = 0;

        // ROLLER
        // if (ball->relative_angle < 90 or ball->relative_angle > 270) roller->on();
        // else roller->off();
        roller->on();

    } else { // BALL IS IN MOUTH
        // // DIRECTION & SPEED
        // driver->speed = GAME_SPEED;
        // driver->dir = attack_goal->angle;

        // // ORIENT
        // driver->pid_limit = 50;
        // driver->orient = attack_goal->angle;

        // // ROLLER
        // roller->on();

        // // KICKER
        // if (
        //     abs((compass->angle > 180) ? compass->angle - 360 : compass->angle - (attack_goal->angle > 180) ? attack_goal->angle - 360 : attack_goal->angle) <= 10
        //     and is_goal_visible(attack_goal->area)
        // ) kicker->kick();

        driver->speed = 0;
        roller->on();
    }
    #else
    // DIR e SPEED
    driver->speed = GAME_SPEED;

    if (!is_ball_close(ball->distance)) driver->dir = ball->relative_angle;

    else if (ball->relative_angle < 30)  driver->dir = ball->relative_angle * 2;
    else if (ball->relative_angle > 330) driver->dir = 360 - ((360 - ball->relative_angle) * 2);

    else if (ball->relative_angle < 90)  driver->dir = ball->relative_angle * 2.2;
    else if (ball->relative_angle > 180) driver->dir = 360 - ((360 - ball->relative_angle) * 2.5);

    else if (ball->relative_angle < 160) driver->dir = 160;
    else if (ball->relative_angle > 200) driver->dir = 200;

    else {
        if (!attack_goal->seen) driver->dir = 130;
        else driver->dir = (attack_goal->angle < 180) ? 130 : 230;
    }

    if (!ball->seen) {
        driver->speed = 0;
        driver->dir = 180;
    }

    // ORIENT
    if (ball_presence->is_in_mouth and attack_goal->seen) driver->orient = attack_goal->angle;
    // else if (ball->absolute_angle < 30 or ball->absolute_angle > 330) driver->orient = ball->absolute_angle;
    else if (attack_goal->seen) driver->orient = attack_goal->angle;
    else driver->orient = 0;

    // KICKER
    if (
        is_goal_visible(attack_goal->area) and 
        ball_presence->is_in_mouth and
        (abs(attack_goal->angle - compass->angle) < 30 or
        abs(attack_goal->angle - compass->angle) > 330)
    ) kicker->kick();

    // ROLLER
    if (ball->relative_angle < 30 or ball->relative_angle > 330 or is_ball_close(ball->distance)) roller->on();
    else roller->off();
    #endif
}
