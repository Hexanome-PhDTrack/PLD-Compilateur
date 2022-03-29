#pragma once

#include "error/CustomError.h"
#include "variable/VarData.h"

#include <vector>

class ErrorManager {
private:
    std::vector<CustomError*> errors;

public:
    ErrorManager() {}
    ~ErrorManager();

    void LogErrors();

    inline void AddError(CustomError* error) {
        errors.push_back(error);
    }

    inline bool hasErrors(){
        return(errors.size()>0);
    }
};