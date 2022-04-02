grammar ifcc;

axiom : prog ;

prog: func*
    ;

func : TYPE VAR '(' (TYPE VAR (',' TYPE VAR)*)? ')' block
     ;

block : '{' instr* '}'
      ;

instr: funcReturn
    | varAssign
    | varDefine
    | block
    | ifElseStatement
    | functionCall
    ;

ifElseStatement: IF '(' expr ')' block (ELSE block)?;

funcReturn : RETURN expr ';' ;

varAssign: VAR '=' expr ';';

varDefine: TYPE varDefineMember (',' varDefineMember)* ';';
varDefineMember: VAR ('=' expr)?;

functionCall: VAR '(' (expr (',' expr)*)? ')' ';';

expr: '(' expr ')' # parenthesis
    | expr OP_MUL_DIV expr # mulDiv
    | expr OP_ADD_SUB expr # addSub
    | expr OP_COMPARE expr # compare
    | expr OP_BITWISE expr # bitwiseOp
    | (NOT | MINUS)? (VAR | CONST) # value
    ;

IF : 'if' ;
ELSE : 'else' ;
MINUS : ('-');
NOT: '!';
RETURN : 'return' ;
TYPE: ('int' | 'char');
OP_MUL_DIV: ('*' | '/');
OP_ADD_SUB: ('+' | '-');
OP_COMPARE: ('<' | '>' | '<=' | '>=' | '==' | '!=');
OP_BITWISE: ('|' | '&' | '^');
VAR: [a-zA-Z]+;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
