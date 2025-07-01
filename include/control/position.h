#pragma once

struct Point { int x=0; int y=0; };

class PositionController {
public:
    Point coord{}, sector{};
    bool set{false};

    PositionController();
    void update();
};
