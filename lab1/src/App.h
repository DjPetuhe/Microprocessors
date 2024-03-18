#pragma once

#include "LedPort.h"
#include "Button.h"
#include "Timer.h"

#include <memory>
#include <functional>

class App
{
public:
    App();
    static std::shared_ptr<App> instance();
    void onButtonChange();
    void onTimerElapsed();
private:
    void initRcc();
    static std::shared_ptr<App> s_instance;
    LedPort m_led = LedPort(0);
    LedPort m_led2 = LedPort(1);
    Button m_button;
    Timer m_t;
};