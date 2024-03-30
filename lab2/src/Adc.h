#pragma once

#include "stm32f103x6.h"

extern "C" void ADC1_2_IRQHandler();

class Adc
{
    friend void ADC1_2_IRQHandler();
public:
    Adc() = default;
    void setup();
    void run();
    uint32_t value();
    bool isChanged();
private:
    static volatile uint32_t s_value;
    static volatile bool changed;
};