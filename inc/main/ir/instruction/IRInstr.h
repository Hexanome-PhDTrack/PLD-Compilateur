

class IRInstr{
    public:
        /**  constructor */
        IRInstr(BasicBlock* bb_, Operation op, Type t, vector<string> params);
        
        /** Actual code generation */
        void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
    private:
        BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
        Type t;
        vector<string> params;
}