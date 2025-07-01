#include "sensors/sensors.h"
#include "control/position.h"

PositionController::PositionController() {}

void PositionController::update() {
    if (attack_goal->seen and defence_goal->seen) {
        int attack_angle = (90-attack_goal->angle) % 360;
        int defence_angle = (90-defence_goal->angle) % 360;

        bool attack_vertical = attack_angle == 90 or attack_angle == 270;
        bool defence_vertical = defence_angle == 90 or defence_angle == 270;

        double attack_goal_slope = tan(radians(attack_angle));
        double defence_goal_slope = tan(radians(defence_angle));

        // y = attack_goal_slope * x + 100
        // y = defence_goal_slope * x - 100
        // x = (-100 - (+100)) / (attack_goal_slope - defence_goal_slope)
        if ((double)(attack_goal_slope - defence_goal_slope) == 0) set = false;
        else if (attack_vertical or defence_vertical) set = false;
        else {
            coord.x = -200 / (attack_goal_slope - defence_goal_slope);
            coord.y = attack_goal_slope * coord.x + 100;
            set = true;
        }
    } else {
        set = false;
    }
}
