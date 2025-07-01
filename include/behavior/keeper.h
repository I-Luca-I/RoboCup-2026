#pragma once

#define SAVE_TIME 1000
#define IDLE_TIME 500

// STATES
#define RESET 0
#define DEFEND 1
#define PARRY 2

void keeper();
void goto_goal();
void defend();
void save();
