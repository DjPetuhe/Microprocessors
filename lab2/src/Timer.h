#pragma once

#include "stm32f103x6.h"

class Timer
{
public:
    Timer();

    void run();
    void enableCMSIS();
    void changeTime(float seconds);
    void changePercentage(float percents);
private:
    float timerSeconds = 1;
    float pwmPercentage = 0.25;
    void update();
};