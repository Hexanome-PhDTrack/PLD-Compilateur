#pragma once

#include <string>
#include <iostream>

class Warning {
protected:
    std::string warningMessage;

public:
    Warning(
        std::string message
    ): warningMessage(message) {}
    ~Warning();

    inline void Log() {
        std::cout << warningMessage << std::endl;
    }
};