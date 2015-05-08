/************************ lexan.cxx  04.04. 2013 ********************/
/*************** Scanner *******************************/

#ifndef GLOBAL_H
#include "global.h"
#endif



#define NORW   12   		/* Zahl der reservierten Worte */

#define RWSYMLEN  15		/* Max. Länge reservierter Symbole */






int lineno;					/* Zeilennummer */

int num ;                  	/* Wert einer nt-Konstanten  */
double realnum; 			/* Wert einer real-Konstanten*/

char idname[BSIZE];      /* Name eines Bezeichners ;
			    wird vom Parser weiterverwendet */


char actchar;                /* gelesenes Zeichen */




/*  Um Bezeichner vor reservierten Symbolene unterscheiden zu können,
    wird eine Tabelle reservierte Worte verwendet (restable).

    Die Tabelle enthält Einträge für jedes Schlüsselwort, bestehend aus
    dem Schlüsselwort selbst und dem zugehörigen Tokentyp (Codierung vgl.global.h):

    Bei Erkennen eines möglichen Bezeichners wird zuerst die Tabelle
    der reservierten Symbole durchsucht (lookforres);
    wird ein Schlüsselwort gefunden, liefert lookforres den dem Schlüsselwort
    zugeordneten Tokentyp; sonst 0. Bei Ergebnis 0 liegt dann tatsächlich ein
    Bezeichner vor.
*/




/* Struktur eines Eintrags in der Tabelle reservierter Symbole */


struct ressw {
	char ressymbol [RWSYMLEN];			/* Symbol */
	int token;							/* zugehöriger Tokentyp */
};



/* Tabelle reservierter Worte */


struct ressw restable [] = {
	"const", CONST,
	"var", VAR,
	"procedure", PROCEDURE,
	"call", CALL,
	"begin", BEGIN,
	"end", END,
	"if", IF,
	"then", THEN,
	"while",WHILE,
	"do", DO,
	"int", INT,
	"real", REAL,
	"boolean", BOOL,
	"true", TRUE,
	"false", FALSE,
};





/* Suchen nach einem reservierten Symbol */


int lookforres( char *s)

/* Sucht in Tabelle reservierter Worte nach s und liefert zugehörigen Token
   falls gefunden,sonst 0
*/

{	struct ressw *ptr;

	for ( ptr = restable; ptr < &restable[NORW]; ptr++ )

		if (strcmp (ptr->ressymbol,s) == 0)
			/* Symbol gefunden */
			return (ptr->token);

	return(0);				/* Symbol nicht gefunden */
}






/******************* Initialisieren des Scanners **********************/

/* wird aufgerufen initialize () aus init.cxx ;
   nimmt Vorbesetzungen der Variablen num, idname und lineno vor;
   liest das erste Zeichen aus der Eingabe */



void initlexan()
{
	num = NONE;
	realnum = -0.0;
	idname [0] = NULL;
	lineno = 1;
	fin.get(actchar);	/* Erstes Zeichen der Eingabe lesen */
}


/********** Funktion nextsymbol ************************************************/
/***********zentrale Funktion zum Lesen des
			nächsten lexikalischen Symbols ******************************/


/* identifiziert nächstes lexikalisches Symbol der Eingabe ;
   bei Aufruf muss sich das nächste Eingabezeichen in actchar befinden,

*/

/**    liefert Codierung in Variable token:

       - Konstante:				token == NUM und Wert der Konstanten in Variable num
       - Bezeichner:				token == ID  und Zeiger auf Name in idname
       - Schlüsselwort:			token == Tokentyp des resevierten Symbols nach
       Suche in restable
       - Operatoren,Sonderzeichen :entsprechende Token

**/


int nextsymbol ()
{
	int token;
	char lexbuf[BSIZE] ;		/* Puffer für Eingabezeichen */


	while( !fin.eof())				/* Eingabe-Dateiende nicht erreicht */
	{
		if ( actchar== ' ' || actchar== '\t')
			/*Blank und Tab in Ausgabedatei kopieren und entfernen */
		{
			fout.put(actchar);
			fin.get(actchar);

		}
		else if (actchar== '\n' ||  actchar == '\r')
			/* Newline in Ausgabedatei kopieren, entfernen, Zeilennummer erhöhen */
		{
			fout.put(actchar);
			fin.get(actchar);
			lineno++;
		}
		else if (isdigit(actchar))

		{ /***** actchar ist Ziffer --> Konstanten erkennen  *****/

			char zahl [BSIZE];		/* Puffer für Ziffern */
			int b = 0;			/* Zeichenzahl*/
			const char **error = NULL;
			int doubleflag = 0;

			/* reg. Ausdruck    (digit)+ '.' (digit)+   erkennen ==>
			   solange Ziffern vorhanden --> Konstante */

			while (isdigit(actchar) || actchar == '.') {
				if (actchar == '.')
					doubleflag = 1;
				zahl[b++] = actchar;
				fout.put(actchar);
				fin.get(actchar);
			}

			zahl[b] = '\0'; /* now its a string, just to be sure */

			if (doubleflag) {
				realnum = strtod(zahl, NULL);
				token = REALNUM;
			} else {
				num = strtonum(zahl, INT_MIN, INT_MAX, error);
				if (error != NULL)
					errx(1, "strtonum: %s", *error);
				token = INTNUM;
			}

			return token;

		} else if (isalpha(actchar))
			/***** actchar ist Buchstabe -->  Identifikatoren erkennen ****/
		{


			int b = 0 ;				/* Zeichenzahl */

			/* reg. Ausdruck   letter (letter|digit)*  erkennen ==>
			   solange Buchstaben oder Ziffern folgen --> Identifikator */
			while (isalpha(actchar) || isdigit(actchar)) {
				lexbuf[b++] = actchar;
				fout.put(actchar);
				fin.get(actchar);
			}

			lexbuf[b] = '\0';

			if ((token = lookforres(lexbuf)) != 0) /* is this word reserved? */
				return token;

			token = ID;
			strlcpy(idname, lexbuf, BSIZE);

			return token;
		} else    /***** Sonderzeichen oder Operatoren erkennen ***************/
		{
			int b = 0;

			lexbuf[b] = actchar;
			fout.put(actchar);
			fin.get(actchar);

			lexbuf[++b] = '\0';

			switch(lexbuf[0]) {
			case '=':
				return EQ;
			case '!':
				if (actchar == '=') {
					fout.put(actchar);
					fin.get(actchar);
					return NE;
				}
				exit(333);
			case '<':
				if (actchar == '=') {
					fout.put(actchar);
					fin.get(actchar);
					return LE;
				}
				return LT;
			case '>':
				if (actchar == '=') {
					fout.put(actchar);
					fin.get(actchar);
					return GE;
				}
				return GT;
			case ':':
				if (actchar == '=') {
					fout.put(actchar);
					fin.get(actchar);
					return ASS;
				}
				return COLON;;
			case ',':
				return KOMMA;
			case ';':
				return SEMICOLON;
			case '+':
				return PLUS;
			case '-':
				return MINUS;
			case '*':
				return MULT;
			case '/':
				return DIV;
			case '(':
				return KLAUF;
			case ')':
				return KLZU;
			case '.':
				return PUNKT;
			}
		}

	}/* end while */

 	return(DONE); 	/* EIngabe -Ende erreicht */

}


