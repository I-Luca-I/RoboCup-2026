#pragma once
#include "behavior/behavior.h"

#define YELLOW_GOAL 0
#define BLUE_GOAL 1

#define GOAL_SWITCH SWITCH_3

#ifdef KEEPER
#define is_goal_visible(area) area > 5000
#endif

#ifdef STRIKER
#define is_goal_visible(area) area > 3000
#endif

void readMV();

class Goal {
public:
    int angle{999}, p_angle{0}, raw_angle{999};
    int area{-1}, p_area{0}, raw_area{-1};
    bool seen{false};

    Goal();
    void update();
    void test();
};
