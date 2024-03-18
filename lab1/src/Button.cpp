#include "Button.h"

#include "App.h"

extern "C" void EXTI2_IRQHandler()
{
    App::instance()->onButtonChange();
    EXTI->PR = EXTI_PR_PR2;
}

Button::Button()
{
    GPIOA->CRL &= ~GPIO_CRL_CNF2;
    GPIOA->CRL |= GPIO_CRL_CNF2_1;
    GPIOA->BSRR = GPIO_BSRR_BS2;

    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI2_PA;
    EXTI->RTSR |= EXTI_RTSR_TR2;
    EXTI->FTSR |= EXTI_FTSR_TR2;

    NVIC_EnableIRQ(EXTI2_IRQn);

    EXTI->PR = EXTI_PR_PR2;
    EXTI->IMR |= EXTI_IMR_MR2;
}

bool Button::clicked()
{
    return !(GPIOA->IDR & GPIO_IDR_IDR2);
}