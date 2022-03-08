#pragma once

#include "VarData.h"
#include "TypeName.h"

#include <string>
#include <map>
#include <stack>
#include <vector>
/**
 * manage the variable 
 * 
 */
class VariableManager{
    public:
        /**
         * @brief Get the Variable object with the name
         * 
         * @param name the name of the variable
         * @return VarData the vardata
         */
        VarData getVariable(std::string name);
        /**
         * @brief Add the Variable object with a computed index
         * 
         * @param varName the name of the variable (if name = #temp, considere it as a temp variable and append the number of temp variable. recupere the full name in the vardata)
         * @param lineContext the full line of the variable appeare for the first time
         * @param lineNumber the line number
         * @param typeName the type of the variable
         * @return VarData 
         */
        VarData addVariable(std::string varName, std::string lineContext, size_t lineNumber, TypeName typeName);
        /**
         * @brief remove a variable temp
         * 
         * @param varName the varaible to remove
         * @return true if varName is a temp var and the remove success
         * @return false if varname is a user variable or the remove failed
         */
        bool removeTempVariable(std::string varName);
        /**
         * @brief Get the Temp Variable object
         * 
         * @return std::vector<VarData> all the temp variable
         */
        std::vector<VarData> getTempVariable();
        /**
         * @brief Get the No Temp Variable object
         * 
         * @return std::vector<VarData> all the no temp variable
         */
        std::vector<VarData> getNoTempVariable();

        VariableManager(){}
        virtual ~VariableManager() {}
    
    private:
        /**
         * @brief the free index available
         * 
         */
        std::stack<int> freeIndex;
        /**
         * @brief the max current index
         * 
         */
        int currentVarIndex = 0;
        /**
         * @brief map variable map and variable data
         * 
         */
        std::map<std::string, VarData> varDataCollection;
};