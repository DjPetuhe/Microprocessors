#pragma once

#include "stm32f103x6.h"

class Adc
{
public:
    Adc() = default;
    void setup();
    uint32_t value();
private:
};