#include "variable/TypeName.h"

TypeName getTypeNameFromString(std::string typeName)
{
    if (typeName == "char")
    {
        return TYPE_CHAR;
    }
    else if (typeName == "int")
    {
        return TYPE_INT;
    }
    else if (typeName == "void")
    {
        return TYPE_VOID;
    }
    // array type to implement
}