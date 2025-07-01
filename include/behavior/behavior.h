#pragma once

#include "config.h"

#ifdef ROLL
#define STRIKER
#define POLAR
#define GAME_SPEED 45
#endif

#ifdef ROCK
#define KEEPER
#define POLAR
#define GAME_SPEED 30
#endif

#define SETUP_SPEED 20

void behavior();
