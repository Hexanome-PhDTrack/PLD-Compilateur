#pragma once

#include <string>
#include <iostream>

class Error {
protected:
    std::string errorMessage;

public:
    Error(
        std::string message
    ): errorMessage(message) {}
    ~Error();

    inline void Log() {
        std::cout << errorMessage << std::endl;
    }
};
