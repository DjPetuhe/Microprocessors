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
    m_terminals.setup();
    m_adc.setup();
}

void App::run()
{
    m_t.run();
    m_adc.run();
    while (true)
    {
        if (m_terminals.hasNewCommand())
        {
            m_commandParser.proccess(m_terminals.newCommand());
        }
        if (m_adc.isChanged())
        {
            m_terminals.sendMsg("Adc = " + std::to_string(m_adc.value()) + " \r\n");
        }
    }
}

void App::onCharRecieve(char s)
{
    m_terminals.receiveChar(s);
}