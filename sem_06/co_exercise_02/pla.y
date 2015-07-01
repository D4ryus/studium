/* ---- declarations ---- */
%{
        #include <stdio.h>
        #include "global.h"
        #include "symbol.h"
        #include "error.h"

        struct st_entry *symentry;

        #define YYERROR_VERBOSE

        void yyerror(const char *s)
        {
                printf("Line %d: %s\n", yylineno, s);
        }
%}

%union {
        int num;
        float realnum;
        char idname[300];
}

%token <realnum> REALNUMBER 2562 /* Real-Konstante */
%token <idname> IDENT 257        /* Identifikator */
%token <num> INTNUMBER 2561      /* Int-Konstante */
%token PROCEDURE 260 "procedure"
%token SEMICOLON 276 ";"
%token _BEGIN 262 "begin"
%token FALSCH 289 "false"
%token CONST 258 "const"
%token WHILE 266 "while"
%token PUNKT 283 "."
%token KOMMA 275 ","
%token MINUS 278 "-"
%token KLAUF 281 "("
%token COLON 284 ":"
%token BOOL 287 "boolean"
%token REAL 286 "real"
%token WAHR 288 "true"
%token CALL 261 "call"
%token THEN 265 "then"
%token PLUS 277 "+"
%token MULT 279 "*"
%token KLZU 282 ")"
%token INT 285 "int"
%token VAR 259 "var"
%token END 263 "end"
%token ASS 274 ":="
%token DIV 280 "/"
%token IF 264 "if"
%token DO 267 "do"
%token NE 269 "!="
%token LT 270 "<"
%token LE 271 "<="
%token GT 272 ">"
%token GE 273 ">="
%token EQ 268 "="

%type <num> TYP

%%

PROGRAM: {
                 actsym = create_newsym();
         }
         BLOCK PUNKT
       ;

BLOCK: CONSTDECL
       VARDECL
       PROCDECL
       STATEMENT
     ;

CONSTASS: IDENT EQ INTNUMBER
          {
                  if (lookup_in_actsym($1) != NULL) {
                          error(34);
                  }
                  insert(KONST, $1, $3);
          }
        ;

CONSTASSIGNS: CONSTASS
            | CONSTASSIGNS KOMMA CONSTASS
            ;

CONSTDECL: CONST CONSTASSIGNS SEMICOLON
         | /* empty */
         ;

VARASS: IDENT COLON TYP
        {
                if (lookup_in_actsym($1) != NULL) {
                        error(34);
                }
                if ($3 == REALIDENT) {
                        insert($3, $1, 0);
                } else {
                        insert($3, $1, 0);
                }
        }
      ;

VARASSIGNS: VARASS
          | VARASS KOMMA VARASSIGNS
          ;

VARDECL: VAR VARASSIGNS SEMICOLON
       | /* empty */
       ;

PROCDECL: PROCEDURE IDENT SEMICOLON
          {
                  if (lookup_in_actsym($2) != NULL) {
                          error(34);
                  }
                  symentry = insert(PROC, $2, 0);
                  actsym = symentry->subsym;
          }
          BLOCK SEMICOLON
          {
                  actsym = actsym->precsym;
          }
          PROCDECL
        | /* empty */
        ;

STATEMENTS: STATEMENT SEMICOLON STATEMENTS
          | STATEMENT
          ;

STATEMENT: IDENT ASS EXPRESSION
           {
                   if (lookup($1) == NULL) {
                           error(10);
                   }
                   if ((lookup($1)->type != REALIDENT
                       && lookup($1)->type != INTIDENT)
                       || lookup($1)->type == PROC)
                   {
                           error(11);
                   }
           }
         | CALL IDENT
           {
                   if (lookup($2) == NULL) {
                           error(10);
                   }
                   if ((lookup($2))->type != PROC) {
                           error(11);
                   }
           }
         | _BEGIN STATEMENTS END
         | IF CONDITION THEN STATEMENT
         | WHILE CONDITION DO STATEMENT
         ;

CONDITION: EXPRESSION RELOP EXPRESSION
         ;

RELOP: EQ
     | NE
     | LT
     | LE
     | GT
     | GE
     ;

EXPRESSION: EXPRESSION PLUS TERM
          | EXPRESSION MINUS TERM
          | TERM
          ;

TERM: TERM MULT FACTOR
    | TERM DIV FACTOR
    | FACTOR
    ;

FACTOR: IDENT
        {
                symentry= lookup($1);
                if (symentry== NULL) {
                        error(34);
                }
        }
      | NUMBER
      | KLAUF EXPRESSION KLZU
      ;

NUMBER: INTNUMBER
      | REALNUMBER
      ;

TYP: INT
     {
             $$ = INTIDENT;
     }
   | REAL
     {
             $$ = REALIDENT;
     }
   ;

%%
