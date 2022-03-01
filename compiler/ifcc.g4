grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' expr* RETURN (VAR | CONST) ';' '}' ;

expr: TYPE VAR '=' VAR ';' # varAssign
    | TYPE VAR '=' CONST ';' # constAssign
    ;

RETURN : 'return' ;
TYPE: 'int';
VAR: [a-zA-Z]+;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
