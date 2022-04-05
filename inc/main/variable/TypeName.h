#pragma once

#include <string>

// enum of types
enum TypeName {
    TYPE_INT,
    TYPE_VOID,
    TYPE_ARRAY,
    TYPE_CHAR,
    TYPE_FUNCTION
};

TypeName getTypeNameFromString(std::string typeName);