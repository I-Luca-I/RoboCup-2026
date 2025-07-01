#pragma once
#include <Servo.h>

class Roller {
private: 
    int microseconds{1200};
    bool full_speed{false};
public:
    Servo servo;
    
    Roller();
    void on();
    void off();
    void test();
};
