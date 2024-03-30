#pragma once

#include "stm32f103x6.h"
#include <string>

class Terminals 
{
public:
    Terminals() = default;
    void setup();
    void receiveChar(char s);
    void sendMsg(std::string msg);
    bool hasNewCommand();
    std::string newCommand();

private:
    std::string m_cmd;
    std::string m_tempCmd;
    bool m_receiveCmd = false;
};