/****************** error.cxx *************************/
/* enth�lt eine Reihe von Fehlertexten, die �ber ihre
Nummer verwendet werden k�nnen und jederzeit erweitert
werden k�nnen.

Zur Ausgabe der Fehlertexte wird die Funktion

	error ( int nr)

  verwendet, der die Fehlernummer zu �bergeben ist.
Die Funktion error f�hrt ein exit durch.

Alternativ kann die Funktion

	errortext (char *)

verwendet werden, die den angebebenen Text ausgibt

*****************************************************/

#ifndef GLOBAL_H
#include "global.h"
#endif

extern int lookahead;

/***************** Fehlertexte **********************/

char *errtxt[] =
{
/* 0*/	"Undefined Syntaxerror ",
/* 1*/	"'='erwartet anstelle von ':=' ",
/* 2*/	"Integer-Konstante nach = erwartet ",
/* 3*/	"= nach Idenitikator erwartet ",
/* 4*/	"Nach const,var,procedure Idenifikator erwartet",
/* 5*/	"';' oder ',' fehlt ",
/* 6*/	"Statement oder Deklaration erwartet ",
/* 7*/	"Falsches Symbol nach Statement im Block",
/* 8*/	"Wiederholung erwartet",
/* 9*/	"Falsche Benutzung eines Symbols in Statement",
/*10*/	"Identifikator nicht deklariert",
/*11*/	"Keine Zuweisungen an Konstante oder Prozedurnamen zul�ssig",
/*12*/	"Wertzuweisungsoperator ist ':=' ",
/*13*/	"Nach call ist Identifikator erwartet ",
/*14*/	"Konstante oder Variable in call nicht erlaubt",
/*15*/	"then erwartet",
/*16*/	"end oder ';' erwartet ",
/*17*/	"do erwartet ",
/*18*/	"Falsches Symbol nach Statement",
/*19*/	"Vergleichsoperator erwartet",
/*20*/	"Prozedurname in Ausdruck nicht erlaubt",
/*21*/	"')' fehlt ",
/*22*/	"Symbol nach Faktor nicht erlaubt",
/*23*/	"Ausdruck darf nicht mit diesem Symbol beginnen",
/*24*/	"Zahl zu gro� ",
/*25*/	"Programm zu gro�",
/*26*/	"Prozedurschachtelung zu tief",
/*27*/	"kein Faktor: Name oder Konstante oder ( E) ",
/*28*/	"Symboltabelle voll",
/*29*/	"Lexemfeld voll",
/*30*/	"Statement erwartet" ,
/*31*/	"Punkt am Programmende fehlt",
/*32*/	"unzul�ssiges Eingabezeichen (Scanner)",
/*33*/	"Nach PROGRAM noch Symbole in Eingabedatei",
/*34*/	"Identifikator doppelt deklariert",
/*35*/	"Doppelpunkt erwartet",
/*36*/	"Unzul�ssiger Typ",
/*37*/	"Falsche Eintragsart in Symboltabelle",
/*38*/	"Keine korrekte reelle Konstante ",
/*39*/	"Identifier expected",
/*40*/	"we did not define this error yet!",
/*41*/	"expected procedure"
};

/***************** Fehlerfunktion **********************/

/* Funktion gibt den der Nummer nr entsprechenden Fehlertext aus */
void
error(int nr)
{
	ferr << "Zeile " << lineno << " " << errtxt[nr];
	ferr << " Token " << lookahead;
	exit(1);
}

/* Funktion gibt den angegebenen  Fehlertext aus */
void
errortext(char *text)
{
	ferr << "Zeile" << lineno << text;
	ferr << " Token " << lookahead;
	exit(1);
}

/* Funktion gibt den angegebenen  Warnungstext aus */
void
warningtext(char *text)
{
	ferr << "Zeile" << lineno << text;
}
