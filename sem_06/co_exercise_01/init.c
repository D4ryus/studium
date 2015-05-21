/******************************** init.cxx ************************/

/* Initialisierungen f�r Compiler PL0  */
#ifndef GLOBAL_H
#include "global.h"
#endif
#include <stdio.h>

FILE *fsym;
FILE *ftra;

int tracesw;
int level = 0;

/***************** Initialisierungen durchf�hren ******************/

void
initialize()
{
	ftra = fopen("trace.out", "w+");
	if (ftra == NULL) {
		printf("could not open trace file\n");
		exit(1);
	}
	tracesw = TRUE;

	/* Datei f�r Symboltabellenausgabe �ffnen */
	fsym = fopen("table.out", "w+");
	if (fsym == NULL) {
		printf("could not open table file\n");
		exit(1);
	}
	fprintf(fsym, "**************** Symboltabellen*************\n");

	/* Initialisieren des Scanners */
	initlexan();
}

/************ Endebehandlung bei fehlerfreier �bersetzung *****/
/* zur Zeit nur Ausgabe der Symboltabelle */

void
stop()
{
	/* Symboltabellen ausgeben */
	printsymtab(firstsym);
}
