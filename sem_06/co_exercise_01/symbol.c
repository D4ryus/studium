/********************* symbol.cxx ************************
 * enth�lt Funktionen zum Erzeugen einer Symboltabelle,
 * Eintragen eines Bezeichners, Suchen eines Bezeichners in der
 * Symboltabelle und Ausgabe der Symboltabelle
 * Die Namen der Bezeichner werden nicht direkt in die Symboltebelle,
 * sondern in das Feld lexemes eingetragen; im Symboltabelleneintrag
 * wird ein Zeiger auf den Eintrag in lexemes abgelegt
 */

#ifndef GLOBAL_H
#include "global.h"
#endif

/* Feld f�r Namen der Bezeichner */
char lexemes[STRMAX];
/* zuletzt benutzte Position in lexemes*/
int lastchar = -1;
/* Zeiger auf zum aktuellen Block geh�rende Symboltabelle */
struct symtable *actsym = NULL;
/* Zeiger auf die zum �ussersten Block geh�rende Symboltabelle */
struct symtable *firstsym;

/********** Erzeugen einer neuen (Teil-) Symboltabelle *************/
/********** Eingetragen wird in precsym der Zeiger auf die *********/
/********** aktuelle Symboltabelle  (actym) ************************/
/********** Ergebnis ist ein Zeiger auf die neue Symboltabelle *****/

struct symtable *
create_newsym()
{
	struct symtable *newsym;

	newsym = malloc(sizeof(struct symtable)); /* Neue ST erzeugen */
	newsym->precsym = actsym;	/* Zeiger auf akt. ST eintragen */
	newsym->anzahl = 0;		/* Zahl der Eintr�ge initialisieren */
	newsym->level = level + 1;	/* Blockniveau erh�hen */

	return newsym;
}


/** Suchen eines Bezeichners (char *s) in der gesamten Symboltabelle ***********
 * Die Suche beginnt in der aktuellen Block geh�renden Symboltabelle (actsym),
 * und weiter in den Symboltabellen der �bergeordneten Bl�cke.
 * Wird der Bezeichner gefunden, wird ein Zeiger auf den zugeh�rigen
 * Symbolotabelleneintrag zur�ckgeliefert; wird der Name nicht gefunden NULL
 */
/* Sucht Name s in der aktuellen und �bergeordneten ST */
struct st_entry *
lookup(char *s)
{
	int i;
	struct symtable *sptr; /* ST-Zeiger */

	sptr = actsym; /* Beginnen bei aktueller ST */

	/* Symboltabellen durchsuchen bis zur obersten (==NULL)*/
	while (sptr != NULL) { /* Durchsuche Eintr�ge in der ST */
		for (i = 0; i < sptr->anzahl; i++) {
			if (strcmp(sptr->eintrag[i].name, s) == 0) {
				/* Zeiger auf ST-Eintrag zur�ckliefern */
				return &sptr->eintrag[i];
			}
		}
		/*
		 * Name in durchsuchter Tabelle nicht gefunden;
		 * Zeiger auf umfassende ST setzen
		 */
		sptr = sptr->precsym;
	}

	return(NULL); /* Name in keiner ST gefunden */
}

/********** Suchen eines Bezeichners (char *s) in der lokalen  Symboltabelle **
 * Ein Bezeichner wird in der lokal g�ltigen (aktuellen = actsym) ST gesucht.
 * Die Funktion wird verwendet bei Deklarationen, um Doppeldeklarationen
 * aufzudecken.
 * Wird der Bezeichner gefunden, wird ein Zeiger auf den zugeh�rigen
 * Symboltabelleneintrag zur�ckgeliefert (== Fehlerfall); wird der Name
 * nicht gefunden NULL
 */
/* Sucht Name s in der aktuellen ST */
struct st_entry *
lookup_in_actsym(char *s)
{
	int i;

	/* Durchsuche Eintr�ge in actsym */
	for (i = 0; i < actsym->anzahl; i++) {
		if (strcmp(actsym->eintrag[i].name, s) == 0) {
			/* Name gefunden --> Zeiger auf ST-Eintrag zur�ckliefern */
			return(&actsym->eintrag[i]);
		}
	}

	return(NULL); /* Name in actsym nicht  gefunden */
}

/********** Neuen Eintrag der Art tok in ST einf�gen  *************
 *
 * Parameter ist die Art des Eintrags (int tok)
 * tok == KONST     f. Konstante : Wert der Konstante wird aus num entnommen
 * tok == INTIDENT  f. Bezeichner  vom Typ int
 * tok == REALIDENT f. Bezeichner vom Typ real
 * tok == BOOLIDENT f. Bezeichner vom Typ boolean
 * tok == PROC      f. Prozedur; f�r die Prozedur wird eine neue Symboltabelle
 *                  angelegt und im Feld subsym des neuen Eintrags eingetragen
 *
 * Ein Zeiger auf den einzutragenden Namen befindet sich in idname
 *
 *
 * R�ckgabe ist ein Zeiger auf den neuen ST-EIntrag
 * st_entry * insert(int tok, char * name, int wert)
 */
struct st_entry *
insert(int tok)
{
	int len;
	struct st_entry neu;		/* Neuer ST-Eintrag  */
	struct st_entry *lastentry;	/* Zeiger auf ST-EIntrag */

	len = strlen(idname);		/* L�nge des Namens bestimmen */

	if (actsym->anzahl >= SYMMAX) {	/* Maximale Gr�sse �berschritten ? */
		error(28);
	}
	/* L�nge des Stringpuffers �berschritten ?*/
	if (lastchar + len + 1 >= STRMAX) {
		error(29);
	}

	strcpy(lexemes + lastchar + 1, idname);	/* Name in Feld lexemes ablegen */

	/* Eintrag zusammenstellen */
	neu.token = tok;		/* Art eintragen */
	neu.name = &lexemes[lastchar + 1]; /* Zeiger auf Namen eintragen */
	lastchar = lastchar + len + 1;	/* Character-Zahl erh�hen */
	neu.subsym = NULL;		/* Zeiger auf Unter-ST initialisieren */
	neu.wertaddr = 0;		/* wertaddr initialisieren  */

	switch (tok) { /* Art eintragen abh�ngig von tok */
		case KONST:
			/* Bei Konstante: Wert eintragen */
			neu.wertaddr = num;
			break;
		case INTIDENT:
			/* Bei Identifikator vom Typ int */
			neu.wertaddr = 0;
			fprintf(ftra, "%4d: insert() - INTIDENT\n", lineno);
			break;
		case REALIDENT:   /* Bei Identifikator vom Typ real  */
			neu.wertaddr = 0;
			fprintf(ftra, "%4d: insert() - REALIDENT\n", lineno);
			break;
		case PROC:
			/*
			 * bei Prozedur: ST f�r lokale Deklarationen der
			 * neuen Prozedur erzeugen und Zeiger eintragen
			 */
			neu.subsym = create_newsym();
			break;
		default:
			/* falsche Eintragsart */
			errortext("falsche Eintragsart in Symboltabelle\n");
			break;
	}

	actsym->eintrag[actsym->anzahl] = neu; /* Neuer Eintrag in ST */

	/* Zeiger auf Eintrag bestimmen */
	lastentry = &(actsym->eintrag[actsym->anzahl]);

	/* Anzahl der Eintr�ge erh�hen */
	actsym->anzahl++;

	/* Testausgabe */
	fprintf(ftra, "\tnew entry: token: %d name: %s addr: %d",
	    lastentry->token, lastentry->name, lastentry->wertaddr);

	/* Zeiger auf Eintrag als Returnwert liefern */
	return lastentry;
}

/********** Ausgabe einer Teil-  Symboltabelle ( sptr) *************/
void
printsymtab(struct symtable *sptr)
{
	int i;
	struct st_entry *act;

	fprintf(fsym, "Anzahl der Eintr�ge: %d\nBlockniveau: %d\n",
	    sptr->anzahl, sptr->level);

	/* alle Eintr�ge der ST ausgeben */ 
	for (i =  0; i < sptr->anzahl; i++) {
		act = &(sptr->eintrag[i]);
		fprintf(fsym, "Eintrag-Nr: %d", i + 1);

		/* Name, Art, Wert ausgeben */
		fprintf(fsym, "\t%s\t%d\t%d\n",
		    act->name, act->token, act->wertaddr);

		/* Bei PROC-Eintr�gen --> zur Prozedur geh�rende ST ausg�ben */
		if (act->token == PROC) {
			fprintf(fsym, "Symboltabelle zu\t%s\n", act->name);

			printsymtab(act->subsym);
			fprintf(fsym, "Ende Symboltabelle zu\t%s\n", act->name);
		}
	}
}
