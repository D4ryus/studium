/************************ lexan.cxx  04.04. 2013 ********************/
/*************** Scanner *******************************/

#ifndef GLOBAL_H
#include "global.h"
#endif

#define NORW 12		/* Zahl der reservierten Worte */
#define RWSYMLEN 15	/* Max. L�nge reservierter Symbole */

int lineno;		/* Zeilennummer */
int num;		/* Wert einer nt-Konstanten  */
double realnum;		/* Wert einer real-Konstanten*/
char idname[BSIZE];	/* Name eines Bezeichners */
char actchar;		/* gelesenes Zeichen */

/*
 * Um Bezeichner vor reservierten Symbolene unterscheiden zu k�nnen,
 * wird eine Tabelle reservierte Worte verwendet (restable).
 *
 * Die Tabelle enth�lt Eintr�ge f�r jedes Schl�sselwort, bestehend aus
 * dem Schl�sselwort selbst und dem zugeh�rigen Tokentyp
 * (Codierung vgl.global.h):
 *
 * Bei Erkennen eines m�glichen Bezeichners wird zuerst die Tabelle
 * der reservierten Symbole durchsucht (lookforres);
 * wird ein Schl�sselwort gefunden, liefert lookforres den dem Schl�sselwort
 * zugeordneten Tokentyp; sonst 0. Bei Ergebnis 0 liegt dann tats�chlich ein
 * Bezeichner vor.
 */

/* Struktur eines Eintrags in der Tabelle reservierter Symbole */
struct ressw {
	char ressymbol[RWSYMLEN];	/* Symbol */
	int token;			/* zugeh�riger Tokentyp */
};

/* Tabelle reservierter Worte */
struct ressw restable[] = {
	{"const",	CONST     },
	{"var",		VAR       },
	{"procedure",	PROCEDURE },
	{"call",	CALL      },
	{"begin",	BEGIN     },
	{"end",		END       },
	{"if",		IF        },
	{"then",	THEN      },
	{"while",	WHILE     },
	{"do",		DO        },
	{"int",		INT       },
	{"real",	REAL      },
	{"boolean",	BOOL      },
	{"true",	TRUE      },
	{"false",	FALSE     }
};

/*
 * Suchen nach einem reservierten Symbol
 * Sucht in Tabelle reservierter Worte nach s und liefert zugeh�rigen Token
 * falls gefunden,sonst 0
 */
int
lookforres(char *s)
{
	struct ressw *ptr;

	for (ptr = restable; ptr < &restable[NORW]; ptr++) {
		if (strcmp(ptr->ressymbol,s) == 0) {
			/* Symbol gefunden */
			return ptr->token;
		}
	}

	/* Symbol nicht gefunden */
	return(0);
}

/******************* Initialisieren des Scanners ******************************/

/*
 * wird aufgerufen initialize () aus init.cxx ;
 * nimmt Vorbesetzungen der Variablen num, idname und lineno vor;
 * liest das erste Zeichen aus der Eingabe
 */

void
initlexan()
{
	num = NONE;
	realnum = -0.0;
	idname[0] = '\0';
	lineno = 1;
	/* Erstes Zeichen der Eingabe lesen */
	actchar = fgetc(stdin);
}

/******* Funktion nextsymbol **************************************************/
/******* zentrale Funktion zum Lesen des n�chsten lexikalischen Symbols *******/
/*
 * identifiziert n�chstes lexikalisches Symbol der Eingabe ;
 * bei Aufruf muss sich das n�chste Eingabezeichen in actchar befinden,
 */

/*
 * liefert Codierung in Variable token:
 *
 * - Konstante:		token == NUM und Wert der Konstanten in Variable num
 * - Bezeichner:	token == ID  und Zeiger auf Name in idname
 * - Schl�sselwort:	token == Tokentyp des resevierten Symbols nach
 * Suche in restable
 * - Operatoren,Sonderzeichen :entsprechende Token
 */

int
nextsymbol()
{
	int token;
	char lexbuf[BSIZE]; /* Puffer f�r Eingabezeichen */

	/* Eingabe-Dateiende nicht erreicht */
	while (actchar != EOF) {
		/*Blank und Tab in Ausgabedatei kopieren und entfernen */
		if (actchar == ' ' || actchar == '\t') {
			fputc(actchar, stdout);
			actchar = fgetc(stdin);
		/*
		 * Newline in Ausgabedatei kopieren, entfernen,
		 * Zeilennummer erh�hen
		 */
		} else if (actchar == '\n' ||  actchar == '\r') {
			fputc(actchar, stdout);
			actchar = fgetc(stdin);
			lineno++;
		/***** actchar ist Ziffer --> Konstanten erkennen  *****/
		} else if (isdigit(actchar)) {
			char zahl [BSIZE];	/* Puffer f�r Ziffern */
			int b = 0;		/* Zeichenzahl*/
			const char **error = NULL;
			int doubleflag = 0;
			char peek_char;
			/*
			 * eg. Ausdruck (digit) + '.' (digit) + erkennen ==>
			 * solange Ziffern vorhanden --> Konstante
			 */
			while (isdigit(actchar) || (actchar == '.')) {
				if (actchar == '.') {
					if (doubleflag) {
						break;
					}
					peek_char = fgetc(stdin);
					ungetc(peek_char, stdin);
					if (isdigit(peek_char)) {
						doubleflag = 1;
					} else {
						break;
					}
				}
				zahl[b++] = actchar;
				fputc(actchar, stdout);
				actchar = fgetc(stdin);
			}
			zahl[b] = '\0'; /* now its a string, just to be sure */
			if (doubleflag) {
				realnum = strtod(zahl, NULL);
				token = REALNUM;
			} else {
				num = strtonum(zahl, INT_MIN, INT_MAX, error);
				if (error != NULL) {
					errx(1, "strtonum: %s", *error);
				}
				token = INTNUM;
			}
			return token;
		/***** actchar ist Buchstabe --> Identifikatoren erkennen ****/
		} else if (isalpha(actchar)) {
			int b = 0; /* Zeichenzahl */
			/*
			 * reg. Ausdruck letter (letter|digit)* erkennen ==>
			 * solange Buchstaben oder Ziffern folgen Identifikator
			 */
			while (isalpha(actchar) || isdigit(actchar)) {
				lexbuf[b++] = actchar;
				fputc(actchar, stdout);
				actchar = fgetc(stdin);
			}

			lexbuf[b] = '\0';

			/* is this word reserved? */
			if ((token = lookforres(lexbuf)) != 0) {
				return token;
			}

			token = ID;
			strlcpy(idname, lexbuf, BSIZE);

			return token;
		/***** Sonderzeichen oder Operatoren erkennen ***************/
		} else {
			int b = 0;

			lexbuf[b] = actchar;
			fputc(actchar, stdout);
			actchar = fgetc(stdin);

			lexbuf[++b] = '\0';

			switch (lexbuf[0]) {
				case '=':
					return EQ;
				case '!':
					if (actchar == '=') {
						fputc(actchar, stdout);
						actchar = fgetc(stdin);
						return NE;
					}
					exit(333);
				case '<':
					if (actchar == '=') {
						fputc(actchar, stdout);
						actchar = fgetc(stdin);
						return LE;
					}
					return LT;
				case '>':
					if (actchar == '=') {
						fputc(actchar, stdout);
						actchar = fgetc(stdin);
						return GE;
					}
					return GT;
				case ':':
					if (actchar == '=') {
						fputc(actchar, stdout);
						actchar = fgetc(stdin);
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
				default:
					error(0);
			}
		}

	} /* end while */

	return DONE; /* Eingabe-Ende erreicht */
}
