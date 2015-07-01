%{
        #include <math.h>
        #include <stdio.h>
        #include <string.h>

        #include "pla.tab.h"
%}

%option yylineno

DIGIT  [0-9]
LETTER [a-zA-Z]

%%

"procedure" return PROCEDURE;
"begin" return _BEGIN;
"const" return CONST;
"while" return WHILE;
"then" return THEN;
"call" return CALL;
"real" return REAL;
"var" return VAR;
"end" return END;
"int" return INT;
":=" return ASS;
"if" return IF;
"do" return DO;
"!=" return NE;
">=" return GE;
"<=" return LE;
";" return SEMICOLON;
"," return KOMMA;
"-" return MINUS;
"." return PUNKT;
":" return COLON;
"(" return KLAUF;
"+" return PLUS;
"*" return MULT;
")" return KLZU;
"/" return DIV;
"=" return EQ;
"<" return LT;
">" return GT;

[0-9]+\.[0-9]+ {
        yylval.realnum = (float)atof(yytext);
        return REALNUMBER;
}

[0-9]+ {
        yylval.num = atoi(yytext);
        return INTNUMBER;
}

[a-zA-Z][a-zA-Z0-9]* {
        strncpy(yylval.idname, yytext, sizeof(yylval.idname));
        return IDENT;
}

[ \t\n\r]

. {
        fprintf(stderr, "Line %d: unknown character: %s\n",
            yylineno, yytext);
        exit(1);
}

%%
