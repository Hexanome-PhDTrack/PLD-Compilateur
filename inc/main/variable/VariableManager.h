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
        static const std::string TEMP_BASE_NAME;


        int getScopeDepth(std::string fullName);

        /**
         * Checks if a variable is already defined in all accessible scope
         * @param name name of the variable
         * @param scope of the variable
         * @return true if var exists, false otherwise
         */
        bool checkVarExists(std::string name, std::string scope);

        /**
         * Checks if a variable is already defined in this scope
         * @param name name of the variable
         * @param scope of the variable
         * @return true if var exists, false otherwise
         */
        bool checkVarExistsInScope(std::string name, std::string scope);

        /**
         * @brief Get the Variable object with the name
         *
         * @param name the name of the variable
         * @return VarData the vardata
         */
        VarData getVariable(std::string name, std::string scope);
        /**
         * @brief Add the Variable object with a computed index
         *
         * @param fullName the name of the variable (if name = #temp, considere it as a temp variable and append the number of temp variable. recupere the full name in the vardata)
         * @param lineNumber the line number
         * @param typeName the type of the variable
         * @param scope the scope of the variable

         * @return VarData the new variable if the name hasn't already taken, the old one otherwise.
         */
        VarData addVariable(std::string fullName, size_t lineNumber, TypeName typeName, std::string scope);
        /**
         * @brief Add the Variable object with a computed index and a constante in
         *
         * @param varName the name of the variable (if name = #temp, considere it as a temp variable and append the number of temp variable. recupere the full name in the vardata)
         * @param lineNumber the line number
         * @param typeName the type of the variable
         * @param value the value of the constante
         * @param scope the scope of the variable

         * @return VarData the new variable if the name hasn't already taken, the old one otherwise.
         */
        VarData addConst(std::string varName, size_t lineNumber, TypeName typeName, int value, std::string Scope);
        /**
         * @brief remove a variable temp with the name
         *
         * @param varName the varaible to remove
         * @param scope the scope of the variable
e
         * @return true if varName is a temp var and the remove success
         * @return false if varname is a user variable or the remove failed
         */
        bool removeTempVariable(std::string varName,std::string scope);

        /**
         * @brief remove a variable temp with the name
         *
         * @param varName the varaible to remove
         * @return true if varName is a temp var and the remove success
         * @return false if varname is a user variable or the remove failed
         */
        bool removeTempVariable(std::string varName);


    /**
         * @brief remove a variable temp
         *
         * @param var the varaible to remove
         * @return true if varName is a temp var and the remove success
         * @return false if varname is a user variable or the remove failed
         */
        bool removeTempVariable(VarData var);
        /**
         * @brief Get the Temp Variable object
         *
         * @return std::vector<VarData> all the temp variable
         */
        std::vector<VarData> getTempVariables() const;
        /**
         * @brief Get the No Temp Variable object
         *
         * @return std::vector<VarData> all the no temp variable
         */
        std::vector<VarData> getNoTempVariables() const;

        VariableManager(){}
        virtual ~VariableManager() {}

        // getters
        inline int GetStackFrameByteSize() const
        {
            return stackFrameByteSize;
        }

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
         * @brief count all the temp var create
         *
         */
        int countAllTempVar = 0;
        /**
         * @brief map variable name and variable data
         *
         */
        std::map<std::string, VarData> varDataCollection;
        // size in byte of all allocated local variables
        int stackFrameByteSize = 0; 

        /**
         * @brief compute the next index and update freeIndex or currentVarIndex
         *
         * @return int the next index (considere to be used)
         * @param type the type of the last variable
         */
        int computeNextIndex(TypeName type);

        /**
         * @brief test if a var is a temp one
         *
         * @param varName the variable name
         * @return true if the variable is temp
         * @return false
         */
        bool isTemp(std::string varName) const;

        /**
         * @brief Get the Full Name of variable in symbole table given scope and variable name
         * 
         * @param name the name of the variable
         * @param scope the scope
         * @return std::string 
         */
        std::string getVariableFullName(std::string name, std::string scope);
};