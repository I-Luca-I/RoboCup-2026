#pragma once

#define BALL_PRESENCE_THRESHOLD 1200

class BallPresence {
public:
    int p_value{0}, value{0};
    bool is_in_mouth{false};

    BallPresence();
    void update();
};
