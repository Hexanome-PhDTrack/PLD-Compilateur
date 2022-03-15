grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' expr* RETURN computedValue ';' '}' ;

expr: varAssign
    | varDefine
    ;

varAssign: VAR '=' computedValue ';';

varDefine: TYPE varDefineMember (',' varDefineMember)* ';';
varDefineMember: VAR ('=' computedValue)?;

computedValue: '(' computedValue ')' # parenthesis
    | computedValue OP_MUL_DIV computedValue # mulDiv
    | computedValue OP_ADD_SUB computedValue # addSub
    | (VAR | CONST) # value
    ;

RETURN : 'return' ;
TYPE: 'int';
OP_MUL_DIV: ('*' | '/');
OP_ADD_SUB: ('+' | '-');
VAR: [a-zA-Z]+;
CONST : [-]?[0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
