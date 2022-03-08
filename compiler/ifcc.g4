grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' expr* RETURN computedValue ';' '}' ;

expr: varAssign
    | varDefine
    ;

varAssign: VAR '=' computedValue ';';

varDefine: TYPE VAR ('=' computedValue)? ';';

computedValue: computedValue2;
computedValue2: computedValue2 ('*' | '/') computedValue2 # mulDiv
    | computedValue2 ('+' | '-') computedValue2 # addSub
    | '(' computedValue2 ')' # parenthesis
    | (VAR | CONST) # value
    ;

RETURN : 'return' ;
TYPE: 'int';
OP_MUL_DIV: ('*' | '/');
OP_ADD_SUB: ('+' | '-');
VAR: [a-zA-Z]+;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
