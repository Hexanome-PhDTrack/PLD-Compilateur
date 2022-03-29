#include "ir/instruction/SubInstr.h"

void SubInstr::gen_x86_asm(std::ostream &o)
{
  o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
  o << "	subl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
  o << "  movl "
    << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};

void SubInstr::gen_arm_asm(std::ostream &o)
{

}