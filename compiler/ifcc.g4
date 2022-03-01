grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' EXPR RETURN CONST ';' '}' ;

EXPR: EXPR2;
EXPR2: TYPE ' ' VAR '=' VAR ';'
    | TYPE ' ' VAR '=' CONST ';';

RETURN : 'return' ;
TYPE: 'int';
VAR: [a-zA-Z]+;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
