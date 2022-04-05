grammar ifcc;

axiom : prog ;

prog: func+
    ;

func : TYPE VAR '(' (TYPE VAR (',' TYPE VAR)*)? ')' block
     ;

block : '{' instr* '}'
      ;

instr: funcReturn
    | varAssign
    | varDefine
    | block
    | call
    ;

funcReturn : RETURN expr ';' ;

varAssign: VAR '=' expr ';';

varDefine: TYPE varDefineMember (',' varDefineMember)* ';';
varDefineMember: VAR ('=' expr)?;

call: functionCall ';';
functionCall: VAR '(' (expr (',' expr)*)? ')';

expr: '(' expr ')' # parenthesis
    | expr OP_MUL_DIV expr # mulDiv
    | expr OP_ADD_SUB=('+' | '-') expr # addSub
    | expr OP_COMPARE expr # compare
    | expr OP_BITWISE expr # bitwiseOp
    | (NOT | MINUS='-')? (VAR | CONST) # value
    | (NOT | MINUS='-')? functionCall # callAndGet
    ;


NOT: '!';
RETURN : 'return' ;
TYPE: ('void' | 'int' | 'char');
OP_MUL_DIV: ('*' | '/');
OP_COMPARE: ('<' | '>' | '<=' | '>=' | '==' | '!=');
OP_BITWISE: ('|' | '&' | '^');
VAR: [a-zA-Z][0-9a-zA-Z]*;
CONST : [0-9]+ ;
MULTI_LINE_COMMENT : '/*' .*? '*/' -> skip ;
SINGLE_LINE_COMMENT : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
