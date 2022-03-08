#include <string>
#include "TypeName.h"

class VarData {
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

private:
    bool isUsed = false;

};