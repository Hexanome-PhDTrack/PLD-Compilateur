grammar ifcc;

axiom : prog ;

prog: func*
    ;

func : TYPE VAR '(' ')' block
     | TYPE VAR '(' TYPE VAR (',' TYPE VAR)* ')' block
     ;

block : '{' expr* '}'
      ;

expr: funcReturn
    | varAssign
    | varDefine
    ;

funcReturn : RETURN computedValue ';' ;

varAssign: VAR '=' computedValue ';';

varDefine: TYPE varDefineMember (',' varDefineMember)* ';';
varDefineMember: VAR ('=' computedValue)?;

computedValue: '(' computedValue ')' # parenthesis
    | computedValue OP_MUL_DIV computedValue # mulDiv
    | computedValue OP_ADD_SUB computedValue # addSub
    | MINUS? (VAR | CONST) # value
    ;

MINUS : ('-');

RETURN : 'return' ;
TYPE: 'int';
OP_MUL_DIV: ('*' | '/');
OP_ADD_SUB: ('+' | '-');
VAR: [a-zA-Z]+;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
