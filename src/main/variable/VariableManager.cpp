#include "variable/VariableManager.h"
#include <iostream>

const std::string VariableManager::TEMP_BASE_NAME = "#tmp";

int VariableManager::computeNextIndex(TypeName type)
{
    /*if (freeIndex.size() > 0)
    {
        // TODO: Handle chars
        int toReturn = freeIndex.top();
        freeIndex.pop();
        return toReturn;
    }
    else
    {*/
        std::cout << "Current index: " << currentVarIndex << "\t";
        switch (type)
        {
            case TYPE_CHAR:
                std::cout << "New index: " << (currentVarIndex - 1) << "\t(Type char)" << std::endl;
                return (currentVarIndex -= 1);

            case TYPE_INT:
            default:
                if (currentVarIndex % 4 != 0)
                {
                    currentVarIndex = -currentVarIndex;
                    currentVarIndex = (-1) * (currentVarIndex - (currentVarIndex % 4) + 4);
                }
                std::cout << "New index: " << (currentVarIndex - 4) << "\t(Type int)" << std::endl;
                return (currentVarIndex -= 4);
        }
    //}
}

bool VariableManager::isTemp(std::string varName) const
{
    return varName.substr(0, TEMP_BASE_NAME.size()) == TEMP_BASE_NAME;
}

///////////////////////////////////////////////////////////////////////////

bool VariableManager::checkVarExists(std::string name)
{
    std::map<std::string, VarData>::iterator it = varDataCollection.find(name);
    return it != varDataCollection.end();
}
VarData VariableManager::getVariable(std::string name)
{
    varDataCollection.at(name).WitnessUsage(); // var used
    return varDataCollection.find(name)->second;
}

VarData VariableManager::addVariable(std::string varName, size_t lineNumber, TypeName typeName)
{
    std::cout << "Adding to VariableManager with typename " << typeName << std::endl;
    // check if the name is already take
    std::map<std::string, VarData>::iterator it = varDataCollection.find(varName);
    if (it != varDataCollection.end())
    {
        return it->second;
    }
    else
    {
        std::cout << "Computing next index with typename " << typeName << std::endl;
        int newIndex = computeNextIndex(typeName);
        // if temp var, update with nex index
        if (varName == TEMP_BASE_NAME)
        {
            varName += countAllTempVar;
            countAllTempVar++;
        }
        VarData newVar = VarData(
            newIndex,
            varName,
            lineNumber,
            typeName,
            false);

        varDataCollection.insert(
            std::pair<std::string, VarData>(
                varName,
                newVar));
        return newVar;
    }
}

VarData VariableManager::addConst(std::string varName, size_t lineNumber, TypeName typeName, int value)
{
    // check if the name is already take
    std::map<std::string, VarData>::iterator it = varDataCollection.find(varName);
    if (it != varDataCollection.end())
    {
        return it->second;
    }
    else
    {
        int newIndex = computeNextIndex(typeName);
        // if temp var, update with nex index
        if (varName == TEMP_BASE_NAME)
        {
            varName += countAllTempVar;
            countAllTempVar++;
        }
        VarData newVar = VarData(
            newIndex,
            varName,
            lineNumber,
            typeName,
            true);
        newVar.SetValue(value);

        varDataCollection.insert(
            std::pair<std::string, VarData>(
                varName,
                newVar));
        return newVar;
    }
}

bool VariableManager::removeTempVariable(std::string varName)
{
    // if temp var
    if (isTemp(varName))
    {
        std::map<std::string, VarData>::iterator it = varDataCollection.find(varName);
        if (it != varDataCollection.end())
        {
            freeIndex.push((*it).second.GetIndex());
            varDataCollection.erase(it);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool VariableManager::removeTempVariable(VarData var)
{
    return removeTempVariable(var.GetVarName());
}

std::vector<VarData> VariableManager::getTempVariables() const
{
    std::vector<VarData> toReturn;
    for (auto elt : varDataCollection)
    {
        VarData actu = elt.second;
        if (isTemp(actu.GetVarName()))
        {
            toReturn.push_back(actu);
        }
    }
    return toReturn;
}

std::vector<VarData> VariableManager::getNoTempVariables() const
{
    std::vector<VarData> toReturn;
    for (auto elt : varDataCollection)
    {
        VarData actu = elt.second;
        if (!isTemp(actu.GetVarName()))
        {
            toReturn.push_back(actu);
        }
    }
    return toReturn;
}
