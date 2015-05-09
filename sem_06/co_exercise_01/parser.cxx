/************************* parser.cxx 04.04.2013 ******************************/

#ifndef GLOBAL_H
#include "global.h"
#endif

int lookahead; /* lookahead enthält nächsten EIngabetoken */

int exp();
int nextsymbol();

/** FACTOR *********************************************************************
 *
 * analysiert wird der korrekte Aufbau eines Faktors nach folgender Syntax:
 *
 * FACTOR ::= IDENT |  NUMBER | '('  EXPRESSION  ')'
 *
 * Schnittstelle:
 * bei Aufruf: nächstes Eingabesymbol befindet sich in lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 *
 * Typ des Faktors ist F-Wert
 */
int
factor()
{
	int kind;
	st_entry *found; // Zeiger auf Eintrag in ST
	int factor_typ;

	if (tracesw) {
		trace << lineno << ": faktor()\n";
	}

	// je nach nächstem Eingabesymbol in lookahead
	switch (lookahead) { // je nach nächstem Eingabesymbol in lookahead
		case KLAUF: /* Symbol '(' folgt --> (EXPRESSION) erwartet*/
			lookahead = nextsymbol();
			factor_typ = exp();
			if (lookahead == KLZU) {
				// korrekt ; nächstes Symbol lesen --> Ende
				lookahead = nextsymbol();
			} else {
				error(27); // kein Faktor
			}
			break;
		case INTNUM:
			/* Int-Zahl (INTNUMBER) gefunden --> okay */
			lookahead = nextsymbol();
			break;
		case REALNUM:
			/* Real-Zahl (REALNUMBER) gefunden --> okay */
			lookahead = nextsymbol();
			break;
		case ID:
			/*
			 * Identifikator (ID) gefunden
			 * Suche Identifikator in Symboltabelle ;
			 * angewandtes Auftreten -->
			 * Deklaration muss vorhanden sein
			 * und also Eintrag in ST
			 */
			found = lookup(idname);
			if (found == NULL) {
				/* nicht gefunden --> Fehler: Id nicht deklariert*/
				error(10);
			} else { // Id in ST gefunden ; Art prüfen
				kind = found->token; // Art des ST-Eintrags
				switch (kind) {
					case KONST:
						// Konstantenname --> okay
						break;
					case INTIDENT:
						// einfache Variable, Typ int --> okay
						break;
					case REALIDENT:
						// einfache Variable, Typ real --> okay
						break;
					case PROC:
						// Name einer Prozedur in
						// Factor nicht erlaubt
						error(20); // --> exit
						// break;
				}
				// nächstes Symbol lesen
				lookahead=nextsymbol();
			}
			break;
		default:
			// kein korrekter Faktor
			error (27);
	}

	return 0;
} // end factor

/** TERM ***********************************************************************
 *
 * analysiert wird der korrekte Aufbau eines Terms nach folgender Syntax:
 *
 * TERM ::= FACTOR  { '*' FACTOR |  '/' FACTOR }*
 *
 * Schnittstelle:
 * bei Aufruf: nächstes Eingabesymbol befindet sich in lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 *
 * Typ des Terms ist Funktionswert
 */
int
term()
{
	int typ_left;
	int typ_right;

	if (tracesw) {
		trace << lineno << ": term()\n";
	}

	typ_left = factor();
	// korrekter Factor

	// solange * oder / folgt, muss Factor kommen
	while ((lookahead == MULT) || (lookahead == DIV)) {
		// nächstes Symbol lesen
		lookahead = nextsymbol();
		// Factor prüfen
		typ_right = factor();
		// nach korrektem Ende wurde nächstes Symbol gelesen
	}

	return 0; // end term
}

/** EXPRESSION *****************************************************************
 *
 * analysiert wird der korrekte Aufbau eines Ausdrucks nach folgender Syntax:
 *
 * EXPRESSION ::= TERM { '+' TERM |  '-' TERM}*
 *
 * Schnittstelle:
 * bei Aufruf: nächstes Eingabesymbol befindet sich in lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 *
 * Funktionswert ist Typ des Ausdrucks
 */

int
exp()
{
	int typ_left;
	int typ_right;

	if (tracesw) {
		trace << lineno << ": exp()\n";
	}

	typ_left = term();
	// korrekter Term

	// solange + oder - folgt, muss Term kommen
	while ((lookahead == PLUS) || (lookahead == MINUS)) {
		// nächstes Symbol lesen
		lookahead = nextsymbol();
		// Term prüfen
		typ_right = term();
		// nach korrektem Ende wurde nächstes Symbol gelesen
	}

	return 0;
} // end exp

/** CONDITION ******************************************************************
 *
 * analysiert wird der korrekte Aufbau einer Bedingung nach folgender Syntax:
 *
 * CONDITION ::= EXPRESSION  RELOP  EXPRESSION
 *
 * Schnittstelle:
 * bei Aufruf: nächstes Eingabesymbol befindet sich in lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 */
int
condition()
{
	int typ_left;
	int typ_right;

	if (tracesw) {
		trace << lineno << ": condition()\n";
	}

	typ_left = exp();
	// korrekter Ausdruck
	// relationaler Operator muss folgen

	switch (lookahead) {
		case EQ:
		case NE:
		case LT:
		case LE:
		case GT:
		case GE:
			// nächstes Symbol lesen
			lookahead = nextsymbol();
			// Ausdruck muss folgen
			typ_right = exp();

			break;
		default:
			// kein relationaler Operator
			error(19);
	}
	if (typ_left != typ_right) {
		errortext("Typen der Operanden nicht kompatibel");
	}

	return typ_left;
}  // end condition

/** STATEMENT ******************************************************************
 *
 * analysiert wird der korrekte Aufbau eines Statements nach folgender Syntax:
 *
 * STATEMENT ::= IDENT  ':=' EXPRESSION
 *             | call IDENT
 *             | begin STATEMENT { ';' STATEMENT }* end
 *             | if CONDITION then STATEMENT
 *             | while CONDITION do STATEMENT
 *
 * Schnittstelle:
 * bei Aufruf: nächstes Eingabesymbol befindet sich in lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 */
void
statement()
{
	if (tracesw) {
		trace << lineno << ": statement()\n";
	}

	switch (lookahead) {
		case ID:
			lookahead = nextsymbol();
			if (lookahead != ASS) {
				error(12);
			}
			lookahead = nextsymbol();
			exp();
			break;
		case CALL:
			lookahead = nextsymbol();
			if (lookahead != ID) {
				error(40);
			}
			lookahead = nextsymbol();
			break;
		case BEGIN:
			lookahead = nextsymbol();
			statement();
			if (lookahead != END) {
				error(16);
			}
			lookahead = nextsymbol();
			break;
		case IF:
			lookahead = nextsymbol();
			condition();
			lookahead = nextsymbol();
			if (lookahead != THEN) {
				error(40);
			}
			lookahead = nextsymbol();
			statement();
			break;
		case WHILE:
			lookahead = nextsymbol();
			condition();
			if (lookahead != DO) {
				error(17);
			}
			lookahead = nextsymbol();
			statement();
			break;
	}

	if (lookahead == SEMICOLON) {
		lookahead = nextsymbol();
		statement();
	}

	return; // end statement
}

/** PROCDECL *******************************************************************
 *
 * analysiert wird der korrekte Aufbau einer Prozedurdeklaration
 * nach folgender Syntax:
 *
 * PROCDECL ::= {procedure IDENT ';' BLOCK ';' }*
 *
 * Schnittstelle:
 * bei Aufruf: erkannt wurde das Schlüsselwort procedure nächstes Eingabesymbol
 *             befindet sich in lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 */
void
procdecl()
{
	symtable * neusym; // Zeiger auf neue Symboltabelle

	if (tracesw) {
		trace << lineno << ": procdecl()\n";
	}

	lookahead = nextsymbol();

	if (lookahead == ID) {
		insert(PROC);
	} else {
		error(39);
	}

	lookahead = nextsymbol();

	if (lookahead != SEMICOLON) {
		error(5);
	}

	lookahead = nextsymbol();
	neusym = create_newsym();
	block(neusym);

	return; // end procdecl
}

/** VARDECL ********************************************************************
 *
 * analysiert wird der korrekte Aufbau einer Variablendeklaration
 * nach folgender Syntax:
 *
 * VARDECL ::= var IDENT ' : ' TYP  { ',' IDENT ' : ' TYP} *  ';'
 *
 * Schnittstelle:
 * bei Aufruf: erkannt wurde das Schlüsselwort var nächstes Eingabesymbol
 *             befindet sich im lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 */
void
vardecl()
{
	if (tracesw) {
		trace << lineno << ": vardecl()\n";
	}

	int running;

	running = 1;
	while (running) {
		lookahead = nextsymbol();
		if (lookahead != ID) {
			error(39);
		}

		lookahead = nextsymbol();

		if (lookahead != COLON) {
			error(35);
		}

		lookahead = nextsymbol();
		if (lookahead == INT) {
			insert(INTIDENT);
		} else if (lookahead == REAL) {
			insert(REALIDENT);
		} else {
			error(36);
		}
		lookahead = nextsymbol();
		if (lookahead != KOMMA) {
			running = 0;
		}
	}

	if (lookahead != SEMICOLON) {
		error(5);
	}

	lookahead = nextsymbol();

	return; // ende vardecl
}

/** CONSTDECL ******************************************************************
 *
 * analysiert wird der korrekte Aufbau einer Variablendeklaration nach folgender
 * Syntax:
 *
 * CONSTDECL ::= const IDENT '=' NUMBER {',' IDENT '=' NUMBER } * ';'
 *
 * Schnittstelle:
 * bei Aufruf: erkannt wurde das Schlüsselwort const
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 */
void
constdecl()
{
	if (tracesw) {
		trace << lineno << ": constdecl()\n";
	}

	int running = 1;
	while (running) {
		lookahead = nextsymbol();
		if (lookahead != ID) {
			error(39);
		}
		lookahead = nextsymbol();
		if (lookahead != EQ) {
			error(3);
		}
		lookahead = nextsymbol();
		if (lookahead == INTNUM) {
			insert(KONST);
		} else {
			error(36);
		}
		lookahead = nextsymbol();
		if (lookahead != KOMMA) {
			running = 0;
		}
	}

	if (lookahead != SEMICOLON) {
		error(5);
	}

	lookahead = nextsymbol();

	return; // end constdecl
}

/** BLOCK **********************************************************************
 *
 * analysiert wird der korrekte Aufbau eines Blockes nach folgender Syntax:
 *
 * BLOCK ::= [ CONSTDECL ]
 *           [ VARDECL ]
 *           PROCDECL
 *           STATEMENT
 *
 * Der Parameter neusym ist ein Zeiger auf die Symboltabelle des zu
 * analysierenden Blockes
 * ===> äussersten (globalen)  Block: firstsym
 * bei Prozeduren: Zeiger auf neu angelegte ST für Prozedur
 *
 * Zu Beginn muss der globale Zeiger actsym auf die neue ST gesetzt werden
 * Vor Verlassen muss actsym wieder auf den vorigen Wert gesetzt werden
 *
 * Schnittstelle:
 * bei Aufruf: nächstes Eingabesymbol befindet sich in lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 */
void
block(symtable *neusym)
{
	if (tracesw) {
		trace << lineno << ": block()\n";
	}

	symtable *tmp;

	tmp = actsym;
	actsym = neusym;

	if (lookahead == CONST) {
		constdecl();
	}
	if (lookahead == VAR) {
		vardecl();
	}
	if (lookahead == PROCEDURE) {
		procdecl();
	}

	statement();

	actsym = tmp;

	return; // end block
}

/** PROGRAM ********************************************************************
 *
 * analysiert wird der korrekte Aufbau eines Programmes nach folgender Syntax:
 *
 * PROGRAM ::= BLOCK '.'
 *
 * Schnittstelle:
 * bei Aufruf: nächstes Eingabesymbol befindet sich in lookahead
 * bei korrektem Ende: nächstes Eingabesymbol befindet sich in lookahead
 */
void
program()
{
	if (tracesw) {
		trace << lineno << ": program()\n";
	}

	// globale Symboltabelle  anlegen (firstsym)
	firstsym = create_newsym();
	actsym = firstsym;

	// erstes Symbol lesen
	lookahead = nextsymbol();

	// Block muss folgen
	block(firstsym);
	// am programmende muss '.' folgen
	if (lookahead == PUNKT) {
		// nächstes Symbol lesen
		lookahead = nextsymbol();
	} else {
		// Punkt fehlt
		error(31);
	}

	// Dateiende erreicht ?
	if (lookahead != DONE) {
		error(33); // noch Symbole in Eingabedatei nach RPOGRAM
	}
}	// end program

