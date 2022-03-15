#include "variable/VariableManager.h"

const std::string VariableManager::TEMP_BASE_NAME = "#tmp";

int VariableManager::computeNextIndex(){
    if(freeIndex.size() > 0){
        int toReturn = freeIndex.top();
        freeIndex.pop();
        return toReturn;
    }else{
        return (-4) * (++currentVarIndex);
    }
}

bool VariableManager::isTemp(std::string varName) const{
    return varName.substr(0, TEMP_BASE_NAME.size()) == TEMP_BASE_NAME;
}

///////////////////////////////////////////////////////////////////////////

bool VariableManager::checkVarExists(std::string name){
    std::map<std::string, VarData>::iterator it = varDataCollection.find(name);
    if(it != varDataCollection.end()) {
        return true;
    }else{
        return false;
    }
}
VarData VariableManager::getVariable(std::string name){
    varDataCollection.at(name).WitnessUsage();//var used
    return varDataCollection.find(name) -> second;
}

VarData VariableManager::addVariable(std::string varName, size_t lineNumber, TypeName typeName){
    // check if the name is already take
    std::map<std::string, VarData>::iterator it = varDataCollection.find(varName);
    if(it != varDataCollection.end()){
        return it -> second;
    }else{
        int newIndex = computeNextIndex();
        // if temp var, update with nex index
        if(varName == TEMP_BASE_NAME){
            varName += countAllTempVar;
            countAllTempVar ++;
        }
        VarData newVar = VarData(
                newIndex,
                varName,
                lineNumber,
                typeName
            );

        varDataCollection.insert(
            std::pair<std::string, VarData>(
                varName,
                newVar
            )
        );
        return newVar;
    }
}

bool VariableManager::removeTempVariable(std::string varName){
    // if temp var
    if(isTemp(varName)){
        std::map<std::string, VarData>::iterator it = varDataCollection.find(varName);
        if(it != varDataCollection.end()){
            freeIndex.push((*it).second.GetIndex()); 
            varDataCollection.erase(it);
            return true;  
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool VariableManager::removeTempVariable(VarData var){
    return removeTempVariable(var.GetVarName());
}


std::vector<VarData> VariableManager::getTempVariables() const{
    std::vector<VarData> toReturn;
    for(auto elt : varDataCollection){
        VarData actu = elt.second;
        if(isTemp(actu.GetVarName())){
            toReturn.push_back(actu);
        }
    }
    return toReturn;
}

std::vector<VarData> VariableManager::getNoTempVariables() const{
    std::vector<VarData> toReturn;
    for(auto elt : varDataCollection){
        VarData actu = elt.second;
        if(!isTemp(actu.GetVarName())){
            toReturn.push_back(actu);
        }
    }
    return toReturn;
}
