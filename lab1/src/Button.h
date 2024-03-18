#pragma once

#include "stm32f103x6.h"

extern "C" void EXTI1_IRQHandler();

class Button
{
public:
    Button();
    bool clicked();
private:
};