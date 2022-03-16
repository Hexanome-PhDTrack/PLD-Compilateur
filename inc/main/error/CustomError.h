#pragma once

#include <iostream>
#include <string>

class CustomError : public std::exception{
protected:
    std::string message;

public:
    CustomError() {} // default constructor

    CustomError(std::string message): message(message) {}
    ~CustomError() {}
    
    const char * what () const throw () { return message.c_str(); }

    inline void Log() {
        if(message.length() > 0) {
            std::cout << "; ⛔ ERROR: " << message << std::endl;
        }
    }
};