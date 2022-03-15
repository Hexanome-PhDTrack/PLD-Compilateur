#pragma once

#include <iostream>
#include <string>

class Error {
protected:
    std::string message;

public:
    Error() {} // default constructor

    Error(std::string message): message(message) {}
    ~Error() {}

    inline void Log() {
        if(message.length() > 0) {
            std::cout << "; ⛔ ERROR: " << message << std::endl;
        }
    }
};