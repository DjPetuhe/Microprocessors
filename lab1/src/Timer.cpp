#include "Timer.h"
#include "App.h"

extern "C" void TIM1_UP_IRQHandler() 
{ 
    App::instance()->onTimerElapsed();
}

Timer::Timer()
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    
    TIM1->PSC = 8000 - 1;
    TIM1->ARR = 1250 - 1;
    TIM1->DIER |= TIM_DIER_UIE;

    NVIC_EnableIRQ(TIM1_UP_IRQn);
    
    enableCMSIS();
}

void Timer::run()
{
    TIM1->CR1 |= TIM_CR1_CEN;
}

void Timer::enableCMSIS()
{
    GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
    GPIOA->CRL |=  GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1;

    GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    GPIOA->CRH |=  GPIO_CRH_MODE8_0 | GPIO_CRH_CNF8_1;

    AFIO->MAPR |= AFIO_MAPR_TIM1_REMAP_0;

    TIM1->CCR1 = 250 - 1;

    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P | TIM_CCER_CC1NE;
    TIM1->BDTR |= TIM_BDTR_MOE;
}