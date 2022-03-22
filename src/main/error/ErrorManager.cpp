#include "error/ErrorManager.h"

ErrorManager::~ErrorManager(){
    if (errors.size() > 0) {
        for (CustomError * error : errors) {
            delete error;
        }
    }
    
}

void ErrorManager::LogErrors() {
    if (errors.size() > 0) {
        for (CustomError * error : errors) {
            error -> Log();
        }
    }
}