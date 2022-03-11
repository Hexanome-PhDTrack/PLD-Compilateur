#pragma once

#include <string>
#include "TypeName.h"

class VarData {

private:
    int index;
    std::string varName;
    size_t lineNumber = 0;
    bool isUsed = false;
    TypeName typeName;
    
public:
    VarData(
        int index,
        std::string varName,
        size_t lineNumber,
        TypeName typeName
    ): 
        index(index),
        varName(varName), 
        lineNumber(lineNumber), 
        typeName(typeName)
    {};
    virtual ~VarData() {}

    inline void WitnessUsage() { isUsed = true; }
    inline bool IsUsed() const { return isUsed; }

    // getters
    inline int GetIndex() const{
        return index;
    }
    inline std::string GetVarName() const{
        return varName; 
    }
    inline size_t GetLineNumber() const{
        return lineNumber;
    }
    inline TypeName GetTypeName() const{
        return typeName;
    }

    // setters
    inline void SetIndex(int index) {
        this->index = index;
    }
    inline void SetVarName(std::string varName) {
        this->varName = varName;
    }
    inline void SetLineNumber(size_t lineNumber) {
        this->lineNumber = lineNumber;
    }
    inline void SetTypeName(TypeName typeName) {
        this->typeName = typeName;
    }

    inline std::string ToString() {
        return "VarData: " + std::to_string(index) 
            + ", " + varName 
            + ", [" + std::to_string(lineNumber) + "]";
    }

};