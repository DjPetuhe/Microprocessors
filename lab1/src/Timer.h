#pragma once

#include "stm32f103x6.h"

class Timer
{
public:
    Timer();
    void run();
    void enableCMSIS();
};