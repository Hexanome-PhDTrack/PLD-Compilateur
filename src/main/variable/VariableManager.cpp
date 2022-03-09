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

bool VariableManager::isTemp(std::string varName){
    return varName.substr(0, TEMP_BASE_NAME.size()) == TEMP_BASE_NAME;
}

///////////////////////////////////////////////////////////////////////////

VarData VariableManager::getVariable(std::string name){
    return varDataCollection.find(name) -> second;
}

VarData VariableManager::addVariable(std::string varName, size_t lineNumber, TypeName typeName){
    // check if the name is already take
    std::map<std::string, VarData>::iterator it = varDataCollection.find(varName);
    if(it == varDataCollection.end()){
        return (*it).second;
    }else{
        int newIndex = computeNextIndex();
        // if temp var, update with nex index
        if(varName == TEMP_BASE_NAME){
            varName += newIndex;
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

std::vector<VarData> VariableManager::getTempVariables(){
    std::vector<VarData> toReturn;
    for(auto elt:varDataCollection){
        VarData actu = elt.second;
        if(isTemp(actu.GetVarName())){
            toReturn.push_back(actu);
        }
    }
    return toReturn;
}

std::vector<VarData> VariableManager::getNoTempVariables(){
    std::vector<VarData> toReturn;
    for(auto elt:varDataCollection){
        VarData actu = elt.second;
        if(!isTemp(actu.GetVarName())){
            toReturn.push_back(actu);
        }
    }
    return toReturn;
}
