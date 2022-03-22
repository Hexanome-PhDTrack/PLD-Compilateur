#pragma once

#include <iostream>
#include <string>

class Warning {
protected:
    std::string message;

public:
    Warning() {} // default constructor

    Warning(std::string message): message(message) {}
    ~Warning() {}

    inline void Log() {
        if(message.length() > 0) {
            std::cerr << "# 🚨 WARNING: " << message << std::endl;
        }
    }
};