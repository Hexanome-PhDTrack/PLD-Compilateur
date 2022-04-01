#include "ir/instruction/AddInstr.h"

void AddInstr::gen_asm(std::ostream& o) {
    /**
     * There are multiple possibilities, depending of the types of the operand
     * and of the result.
     */

    // INT = INT + INT
    if (params.at(0).GetTypeName() == TYPE_INT and
        params.at(1).GetTypeName() == TYPE_INT and
        params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
        o << "	movl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	addl "
          << "%edx, %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = INT + CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_CHAR) {
        o << "	movsbl " << params.at(2).GetIndex() << "(%rbp), %edx \n";
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	addl "
          << "%edx, %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = CHAR + INT
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
        o << "	movl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	addl "
          << "%edx, %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = CHAR + CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_CHAR) {
        o << "	movsbl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
        o << "	movsbl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	addl "
          << "%edx, %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // CHAR = INT + INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
        o << "  movl "
          << "%eax, %edx \n";
        o << "	movl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	addl "
          << "%edx, %eax \n";
        o << "	movb "
          << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // CHAR = INT + CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_CHAR) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
        o << "  movl "
          << "%eax, %edx \n";
        o << "	movzbl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	addl "
          << "%edx, %eax \n";
        o << "	movb "
          << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // CHAR = CHAR + INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "  movl "
          << "%eax, %edx \n";
        o << "	movzbl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	addl "
          << "%edx, %eax \n";
        o << "	movb "
          << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // CHAR = CHAR + CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_CHAR) {
        o << "	movzbl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
        o << "	movzbl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	addl "
          << "%edx, %eax \n";
        o << "	movb "
          << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
};