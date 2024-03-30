#pragma once

#include "Adc.h"
#include "Timer.h"
#include "LedPort.h"
#include "Terminals.h"
#include "CommandParser.h"

#include <memory>
#include <functional>

class App
{
    friend CommandParser;
public:
    App();
    void run();
    void onCharRecieve(char s);
    static std::shared_ptr<App> instance();

private:
    static std::shared_ptr<App> s_instance;

    Adc m_adc;
    Timer m_t;
    LedPort m_led;
    Terminals m_terminals;
    CommandParser m_commandParser;
};