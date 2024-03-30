#include "Adc.h"

void Adc::setup()
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;                                   // увімкнути АЦП, увімкнути режим перетворення
    ADC1->SMPR2 |= ADC_SMPR2_SMP0_0 | ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_2;      // встановлюємо час перевірки значення
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t Adc::value()
{
    ADC1->CR2 |= ADC_CR2_ADON;
    while (!(ADC1->SR & ADC_SR_EOC)) {}
    return ADC1->DR;
}