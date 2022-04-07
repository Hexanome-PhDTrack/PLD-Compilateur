#include "variable/TypeName.h"

TypeName getTypeNameFromString(std::string typeName)
{
    TypeName actualType = TYPE_UNKNOWN;

    if (typeName == "char")
    {
        actualType = TYPE_CHAR;
    }
    else if (typeName == "int")
    {
        actualType = TYPE_INT;
    }
    else if (typeName == "void")
    {
        actualType = TYPE_VOID;
    }
    // array type to implement

    // check actual type is not unknown
    if (actualType == TYPE_UNKNOWN)
    {
        std::cerr << "Unknown type: " << typeName << std::endl;
        exit(1);
    }

    return actualType;
}

std::string getStringFromTypeName(TypeName typeName)
{
    switch(typeName){
        /*case TYPE_ARRAY:
            return "int";*/

        case TYPE_CHAR:
            return "char";

        case TYPE_INT:
            return "int";

        case TYPE_VOID:
            return "void";

        default:
            return "";
    }
}