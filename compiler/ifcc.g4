grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' expr* RETURN computedValue ';' '}' ;

expr: varAssign
    | varDefine
    ;

varAssign: VAR '=' computedValue ';';

varDefine: TYPE VAR ('=' computedValue)? ';';

computedValue: computedValue2;
computedValue2: computedValue2 '+' computedValue2
    | computedValue2 '-' computedValue2
    | computedValue2 '*' computedValue2
    | computedValue2 '/' computedValue2
    | '(' computedValue2 ')'
    | (VAR | CONST)
    ;

RETURN : 'return' ;
TYPE: 'int';
VAR: [a-zA-Z]+;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
