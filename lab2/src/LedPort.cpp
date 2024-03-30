#include "LedPort.h"

LedPort::LedPort()
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL |= GPIO_CRL_MODE1_0;
}

void LedPort::on()
{
    GPIOA->BSRR = GPIO_BSRR_BS1;
}

void LedPort::off()
{
    GPIOA->BSRR = GPIO_BSRR_BR1;
}

void LedPort::toggle()
{
    if (isOn())
    {
        off();
    }
    else
    {
        on();   
    }
}

bool LedPort::isOn()
{
    return GPIOA->ODR & GPIO_ODR_ODR1;
}