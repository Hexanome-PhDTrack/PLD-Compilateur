#include "ir/instruction/BitOrInstr.h"

void BitOrInstr::gen_asm(std::ostream &o) {
    /**
     * There are multiple possibilities, depending of the types of the operand
     * and of the result.
     */

    // INT = INT | INT
    if (params.at(0).GetTypeName() == TYPE_INT and
        params.at(1).GetTypeName() == TYPE_INT and
        params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	orl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = INT | CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_CHAR) {
        o << "	movsbl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	orl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = CHAR | INT
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movsbl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	orl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = CHAR | CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_CHAR) {
        o << "	movzbl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	orb " << params.at(2).GetIndex() << "(%rbp), %al \n";
        o << "	movsbl "
          << "%al, %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // CHAR = INT | INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "  movl "
          << "%eax, %edx \n";
        o << "	movl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	orl "
          << "%edx, %eax \n";
        o << "	movb "
          << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // CHAR = INT | CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_CHAR) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	orb " << params.at(2).GetIndex() << "%al \n";
        o << "	movb "
          << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // CHAR = CHAR | INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	orb " << params.at(1).GetIndex() << "%al \n";
        o << "	movb "
          << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // CHAR = CHAR | CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_CHAR) {
        o << "	movzbl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	orb " << params.at(2).GetIndex() << "%al \n";
        o << "	movb "
          << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
};