#include "error/ErrorManager.h"

void ErrorManager::LogErrors() {
    if (errors.size() > 0) {
        for (CustomError error : errors) {
            error.Log();
        }
    }
}