grammar ifcc;

axiom : prog ;

prog: func+
    ;

func : TYPE VAR '(' (TYPE VAR (',' TYPE VAR)*)? (',' VARIADIC)? ')' block
     ;

block : '{' instr* (funcReturn)? '}'
      ;

instr: varAssign
    | varDefine
    | block
    | call
    | ifElseStatement
    | whileStatement
    ;

ifElseStatement: IF '(' expr ')' block (ELSE block)?;

whileStatement: WHILE '(' expr ')' block ;

funcReturn : RETURN expr ';' ;

varAssign: VAR '=' expr ';';

varDefine: TYPE varDefineMember (',' varDefineMember)* ';';
varDefineMember: VAR ('=' expr)?;

call: functionCall ';';
functionCall: VAR '(' (expr (',' expr)*)? ')';

expr: '(' expr ')' # parenthesis
    | (OP_UNARY | MINUS='-') expr # unaryOp
    | expr OP_MUL_DIV expr # mulDiv
    | expr OP_ADD_SUB=('+' | '-') expr # addSub
    | expr OP_COMPARE expr # compare
    | expr OP_BITWISE expr # bitwiseOp
    | (VAR | CONST | CHAR) # value
    | functionCall # callAndGet
    ;

WHILE : 'while';
IF : 'if' ;
ELSE : 'else' ;
RETURN : 'return' ;
TYPE: ('void' | 'int' | 'char');
OP_UNARY: ('!' | '~');
OP_MUL_DIV: ('*' | '/');
OP_COMPARE: ('<' | '>' | '<=' | '>=' | '==' | '!=');
OP_BITWISE: ('|' | '&' | '^' | '>>' | '<<');
VAR: [a-zA-Z][0-9a-zA-Z]*;
CONST : [0-9]+ ;
CHAR : '\''.'\'';
MULTI_LINE_COMMENT : '/*' .*? '*/' -> skip ;
SINGLE_LINE_COMMENT : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
VARIADIC : '...';
