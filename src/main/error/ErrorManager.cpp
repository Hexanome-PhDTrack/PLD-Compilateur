#include "error/ErrorManager.h"

ErrorManager::~ErrorManager() {
    if (errors.size() > 0) {
        for (Error* error : errors) {
            delete error;
        }
    }
}

void ErrorManager::LogErrors() {
    if (errors.size() > 0) {
        for (Error* error : errors) {
            error->Log();
        }
    }
}