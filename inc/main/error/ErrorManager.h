#pragma once

#include "error/Error.h"
#include "variable/VarData.h"

#include <vector>

class ErrorManager {
private:
    std::vector<Error*> errors;

public:
    ErrorManager() {}
    ~ErrorManager();

    void LogErrors();

    inline void AddError(Error* error) {
        errors.push_back(error);
    }
};