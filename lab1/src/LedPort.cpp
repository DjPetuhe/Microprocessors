#include "LedPort.h"

LedPort::LedPort(int pinIndx)
{
    this->pinIndx = pinIndx;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    if (!pinIndx)
    {
        GPIOA->CRL |= GPIO_CRL_MODE0_0;
    }
    else
    {
        GPIOA->CRL |= GPIO_CRL_MODE1_0;
    }
}

void LedPort::on()
{
    if (!pinIndx)
    {
        GPIOA->BSRR = GPIO_BSRR_BS0;
    }
    else
    {
        GPIOA->BSRR = GPIO_BSRR_BS1;
    }
}

void LedPort::off()
{
    if (!pinIndx)
    {
        GPIOA->BSRR = GPIO_BSRR_BR0;
    }
    else
    {
        GPIOA->BSRR = GPIO_BSRR_BR1;
    }
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
    if (!pinIndx)
    {
        return GPIOA->ODR & GPIO_ODR_ODR0;
    }
    else
    {
        return GPIOA->ODR & GPIO_ODR_ODR1;
    }
}