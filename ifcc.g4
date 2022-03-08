grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' expr* RETURN (VAR | CONST) ';' '}' ;

expr: varAssign
    | varDefine
    ;

varAssign: VAR '=' (VAR | CONST) ';';

varDefine: TYPE VAR ('=' (VAR | CONST))? ';';

RETURN : 'return' ;
TYPE: 'int';
VAR: [a-zA-Z]+;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
