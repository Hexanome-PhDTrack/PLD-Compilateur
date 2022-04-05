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
        //std::cout << "Current index: " << currentVarIndex << "\t";
        switch (type)
        {
            case TYPE_CHAR:
                //std::cout << "New index: " << (currentVarIndex - 1) << "\t(Type char)" << std::endl;
                return (currentVarIndex -= 1);

            case TYPE_INT:
            default:
                if (currentVarIndex % 4 != 0)
                {
                    currentVarIndex = -currentVarIndex;
                    currentVarIndex = (-1) * (currentVarIndex - (currentVarIndex % 4) + 4);
                }
                //std::cout << "New index: " << (currentVarIndex - 4) << "\t(Type int)" << std::endl;
                return (currentVarIndex -= 4);
        }
    //}
}

bool VariableManager::isTemp(std::string varName) const
{
    return varName.substr(0, TEMP_BASE_NAME.size()) == TEMP_BASE_NAME;
}

///////////////////////////////////////////////////////////////////////////

bool VariableManager::checkVarExists(std::string name, std::string scope)
{
    std::string fullName = scope + name;
    std::map<std::string, VarData>::iterator it = varDataCollection.find(fullName);
    return it != varDataCollection.end();
}
VarData VariableManager::getVariable(std::string name, std::string scope)
{
    // TODO: refactor, this function has a huge edge effect
    std::string fullName = scope + name;
    varDataCollection.at(fullName).WitnessUsage(); // var used
    return varDataCollection.find(fullName)->second;
}

VarData VariableManager::addVariable(
    std::string varName,
    size_t lineNumber, 
    TypeName typeName,
    std::string scope
) {
    std::cout << "Adding to VariableManager with typename " << typeName << std::endl;
    // check if the name is already take

    std::string fullName = scope + varName;

    std::map<std::string, VarData>::iterator it = varDataCollection.find(fullName);
    if (it != varDataCollection.end())
    {
        return it->second;
    }
    else
    {
        //std::cout << "Computing next index with typename " << typeName << std::endl;
        int newIndex = computeNextIndex(typeName);
        // if temp var, update with nex index
        if (fullName == scope+TEMP_BASE_NAME)
        {
            fullName += countAllTempVar;
            countAllTempVar++;
        }
        VarData newVar = VarData(
                newIndex,
                fullName,
                lineNumber,
                typeName,
                false);

        varDataCollection.insert(
            std::pair<std::string, VarData>(
                    fullName,
                    newVar
            )
        );
        
        // before returning, update the stack frame size
        switch(newVar.GetTypeName())
        {
            case TYPE_CHAR:
                stackFrameByteSize += 1;
                break;
            case TYPE_INT:
                stackFrameByteSize += 4;
                break;
            default:
                break;
        }

        return newVar;
    }
}

VarData VariableManager::addConst(std::string varName, size_t lineNumber, TypeName typeName, int value, std::string scope)
{
    // check if the name is already take
    std::string fullName = scope + varName;
    std::map<std::string, VarData>::iterator it = varDataCollection.find(fullName);
    if (it != varDataCollection.end())
    {
        return it->second;
    }
    else
    {
        int newIndex = computeNextIndex(typeName);
        // if temp var, update with nex index
        if (fullName == scope+TEMP_BASE_NAME)
        {
            fullName += countAllTempVar;
            countAllTempVar++;
        }
        VarData newVar = VarData(
                newIndex,
                fullName,
                lineNumber,
                typeName,
                true);
        newVar.SetValue(value);

        varDataCollection.insert(
            std::pair<std::string, VarData>(
                    fullName,
                    newVar));
        return newVar;
    }
}

bool VariableManager::removeTempVariable(std::string varName, std::string scope)
{
    std::string fullName = varName+scope;
    // if temp var
    if (isTemp(fullName))
    {
        std::map<std::string, VarData>::iterator it = varDataCollection.find(fullName);
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
