#include <Arduino.h>
#include "sensors/lines.h"
#include "config.h"

Lines::Lines() {
    #ifdef ROCK
    thresholds[0] = 500; //250-950
    thresholds[1] = 500; //450-960
    
    thresholds[2] = 500; //330-920
    thresholds[3] = 500; //280-840
    
    thresholds[4] = 500; //280-950
    thresholds[5] = 500; //280-900
    
    thresholds[6] = 500; //400-960
    thresholds[7] = 500; //360-960
    
    #else
    thresholds[0] = 500; //240-900
    thresholds[1] = 750; //600-950 (when ball present)

    thresholds[2] = 500; //320-850
    thresholds[3] = 750; //650-950
    
    thresholds[4] = 400; //140-600
    thresholds[5] = 250; //100-480
    
    thresholds[6] = 500; //370-900
    thresholds[7] = 750; //510-950
    
    #endif
}

void Lines::read() {
    values[0] = analogRead(Pins::LINE_N_INSIDE);
    values[1] = analogRead(Pins::LINE_N_OUTSIDE);
    values[2] = analogRead(Pins::LINE_E_INSIDE);
    values[3] = analogRead(Pins::LINE_E_OUTSIDE);
    values[4] = analogRead(Pins::LINE_S_INSIDE);
    values[5] = analogRead(Pins::LINE_S_OUTSIDE);
    values[6] = analogRead(Pins::LINE_W_INSIDE);
    values[7] = analogRead(Pins::LINE_W_OUTSIDE);
    
    status = 0;
    if(values[0] > thresholds[0]) status |= 0b10000000;
    if(values[1] > thresholds[1]) status |= 0b01000000;
    if(values[2] > thresholds[2]) status |= 0b00100000;
    if(values[3] > thresholds[3]) status |= 0b00010000;
    if(values[4] > thresholds[4]) status |= 0b00001000;
    if(values[5] > thresholds[5]) status |= 0b00000100;
    if(values[6] > thresholds[6]) status |= 0b00000010;
    if(values[7] > thresholds[7]) status |= 0b00000001;
}
