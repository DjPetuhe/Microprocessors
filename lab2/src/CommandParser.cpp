#include "CommandParser.h"
#include "App.h"

CommandParser::CommandParser()
{
    commands["led"] = &CommandParser::ledCommands;
    commands["timer"] = &CommandParser::timerCommands;
    commands["pwm"] = &CommandParser::pwmCommands;
}

void CommandParser::proccess(std::string commandString)
{
    size_t spaceIndex = commandString.find(' ');
    std::string command, parameter;
    if (spaceIndex != std::string::npos) {
        command = commandString.substr(0, spaceIndex);
        parameter = commandString.substr(spaceIndex + 1);
    }
    else
    {
        command = commandString;
    }
    auto it = commands.find(command);
    if (it != commands.end())
    {
        if(!(this->*(it->second))(parameter))
        {
            App::instance()->m_terminals.sendMsg("Incorrect param " + parameter + "!\r\n");
        }
    }
    else
    {
        App::instance()->m_terminals.sendMsg("Unknowm command " + command + "!\r\n");
    }
}

bool CommandParser::ledCommands(const std::string &parameter)
{
    if (parameter == "on")
    {
        App::instance()->m_led.on();
    }
    else if (parameter == "off")
    {
        App::instance()->m_led.off();
    }
    else
    {
        return false;
    }
    return true;
}

bool CommandParser::timerCommands(const std::string &parameter)
{
    
    float seconds;
    if (!stringToFloat(parameter, seconds))
    {
        return false;
    }
    if (seconds <= 0 || seconds > 1000) 
    {
        return false;
    }
    App::instance()->m_t.changeTime(seconds);
    return true;
}

bool CommandParser::pwmCommands(const std::string &parameter)
{
    float percent;
    if (!stringToFloat(parameter, percent))
    {
        return false;
    }
    if (percent < 0 || percent > 1) 
    {
        return false;
    }
    App::instance()->m_t.changePercentage(percent);
    return true;
}

bool CommandParser::stringToFloat(const std::string& str, float& result)
{
    float number = 0.0f;
    bool inFraction = false;
    float fractionMultiplier = 0.1f;

    if (str.empty())
    {
        return false;
    }
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
        {
            if (inFraction)
            {
                number += (c - '0') * fractionMultiplier;
                fractionMultiplier *= 0.1f;
            }
            else
            {
                number = number * 10.0f + (c - '0');
            }
        }
        else if (c == '.')
        {
            inFraction = true;
        }
        else
        {
            return false;
        }
    }
    result = number;
    return true;
}