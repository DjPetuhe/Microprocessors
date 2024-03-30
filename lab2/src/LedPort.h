#pragma once

#include "stm32f103x6.h"

class LedPort
{
public:
    LedPort();
    
    void on();
    void off();
    void toggle();
    bool isOn();
};