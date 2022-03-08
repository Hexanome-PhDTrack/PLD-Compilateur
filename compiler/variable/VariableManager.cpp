#include "VariableManager.h"

VarData VariableManager::getVariable(std::string name){
    return varDataCollection.find(name) -> second;
}

VarData VariableManager::addVariable