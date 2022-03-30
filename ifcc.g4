grammar ifcc;

axiom : prog ;

prog: func*
    ;

func : TYPE VAR '(' (TYPE VAR (',' TYPE VAR)*)? ')' block
     ;

block : '{' instr* (funcReturn)? '}'
      ;

instr: varAssign
    | varDefine
    | block
    ;

funcReturn : RETURN expr ';' ;

varAssign: VAR '=' expr ';';

varDefine: TYPE varDefineMember (',' varDefineMember)* ';';
varDefineMember: VAR ('=' expr)?;

expr: '(' expr ')' # parenthesis
    | expr OP_MUL_DIV expr # mulDiv
    | expr OP_ADD_SUB expr # addSub
    | MINUS? (VAR | CONST) # value
    ;

MINUS : ('-');

RETURN : 'return' ;
TYPE: ('int' | 'char');
OP_MUL_DIV: ('*' | '/');
OP_ADD_SUB: ('+' | '-');
VAR: [a-zA-Z]+;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
