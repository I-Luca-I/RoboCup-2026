#pragma once
#include <Arduino.h>

class Lines {
public:
    // | N-IN | N-OUT || E-IN | E-OUT || S-IN | S-OUT || W-IN | W-OUT |
    int thresholds[8], values[8];
    byte status{0};

    Lines();
    void read();
};
