#pragma once

#include <string>
#include <map>

#include "Terminals.h"

class CommandParser {
public:
    CommandParser();
    void proccess(std::string commandString);
private:
    std::map<std::string, bool(CommandParser::*)(const std::string&)> commands;

    bool ledCommands(const std::string &parameter);
    bool timerCommands(const std::string &parameter);
    bool pwmCommands(const std::string &paramete);
    bool stringToFloat(const std::string& str, float& result);
};