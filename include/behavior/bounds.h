#pragma once

#define SPEED_LINE_REACT 50

void line_react(byte readStatus, float mult=1);
void stay_on_line(byte readStatus, float mult=1);
bool goto_center();
