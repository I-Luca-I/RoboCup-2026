#pragma once

#include "sensors/bno.h"
#include "sensors/lines.h"
#include "sensors/ball.h"
#include "sensors/camera.h"
#include "sensors/ball_presence.h"

#ifdef SENSORS
#define s_extr
#else
#define s_extr extern
#endif

s_extr BNO* compass;
s_extr Lines* lines;
s_extr Ball* ball;
s_extr HardwareSerial* BallSerial;
s_extr Goal* attack_goal;
s_extr Goal* defence_goal;
s_extr HardwareSerial* CameraSerial;
s_extr BallPresence* ball_presence;

void init_sensors();
void read_sensors();
