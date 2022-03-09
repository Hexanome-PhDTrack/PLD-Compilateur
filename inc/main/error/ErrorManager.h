#pragma once

#include "error/Error.h"
#include "variable/VarData.h"

#include <vector>

class ErrorManager {
private:
    std::vector<Error*> errors;
};