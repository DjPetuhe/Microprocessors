#include "App.h"

std::shared_ptr<App> App::s_instance = nullptr;

std::shared_ptr<App> App::instance()
{
    if (!s_instance)
    {
        s_instance = std::make_shared<App>();
    }
    return s_instance;
}

App::App()
{
    m_led2.on();
    m_t.run();
}

void App::onButtonChange()
{
    if (m_button.clicked())
    {
        m_led.on();
        m_led2.off();
    }
    else
    {
        m_led.off();
        m_led2.on();
    }
}

void App::onTimerElapsed()
{
    if (m_button.clicked())
    {
        m_led.toggle();
    }
    else
    {
        m_led2.toggle();
    }
}

void App::initRcc()
{
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
    RCC->CFGR |= RCC_CFGR_PLLMULL4;

    RCC->CR |= RCC_CR_PLLON;
    while((RCC->CR & RCC_CR_PLLRDY) == 0) {};

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    while((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0) {};

    RCC->CFGR |= RCC_CFGR_HPRE_DIV2;
}