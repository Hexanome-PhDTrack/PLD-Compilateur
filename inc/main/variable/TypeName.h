#pragma once

#include <string>
#include <iostream>

// enum of types
enum TypeName {
    TYPE_INT,
    TYPE_VOID,
    TYPE_ARRAY,
    TYPE_CHAR,
    TYPE_UNKNOWN
};

TypeName getTypeNameFromString(std::string typeName);