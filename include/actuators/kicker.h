#pragma once

#define KICKER_ATK_TIME 100
#define KICKER_CHARGE_TIME 2000
#define KICKER_AREA_THRESHOLD 6000

class Kicker {
private:
    long long int t_charge{0}, t_atk{0};
public:
    Kicker();
    void kick();
    void update();
    void test();
};
