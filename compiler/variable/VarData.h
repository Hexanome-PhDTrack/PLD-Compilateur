#include <string>
#include "variable/TypeName.h"

class VarData {

private:
    int index;
    std::string varName;
    std::string lineContext;
    size_t lineNumber = 0;
    bool isUsed = false;
    TypeName typeName;
    
public:
    int index;
    std::string varName;
    std::string lineContext;
    size_t lineNumber = 0;

    TypeName typeName;

    VarData(
        int index,
        std::string varName,
        std::string lineContext,
        size_t lineNumber,
        TypeName typeName
    ): 
        index(index),
        varName(varName), 
        lineContext(lineContext), 
        lineNumber(lineNumber), 
        typeName(typeName)
    {};
    virtual ~VarData() {}

    inline void WitnessUsage() { isUsed = true; }
    inline bool IsUsed() { return isUsed; }

    // getters
    inline int GetIndex() {
        return index;
    }
    inline std::string GetVarName() {
        return varName; 
    }
    inline std::string GetLineContext() {
        return lineContext;
    }
    inline size_t GetLineNumber() {
        return lineNumber;
    }
    inline TypeName GetTypeName() {
        return typeName;
    }

    // setters
    inline void SetIndex(int index) {
        this->index = index;
    }
    inline void SetVarName(std::string varName) {
        this->varName = varName;
    }
    inline void SetLineContext(std::string lineContext) {
        this->lineContext = lineContext;
    }
    inline void SetLineNumber(size_t lineNumber) {
        this->lineNumber = lineNumber;
    }
    inline void SetTypeName(TypeName typeName) {
        this->typeName = typeName;
    }

};