#pragma once

#include "warning/Warning.h"
#include "variable/VarData.h"

#include <vector>

class WarningManager {
private:
    std::vector<Warning*> warnings;
};