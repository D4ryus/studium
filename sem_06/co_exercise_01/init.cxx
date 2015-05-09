/******************************** init.cxx ************************/

/* Initialisierungen für Compiler PL0  */
#ifndef GLOBAL_H
#include "global.h"
#endif
#include <stdio.h>

ifstream fin;   /* Zu übersetzende Eingaben */
ofstream fout,  /* Ausgabedatei */
	 ferr,  /* Fehlerausgaben */
	 fsym,  /* Ausgabe für Symboltabelle */
	 trace; /* Ausgabe für Trace */

int tracesw;
int level = 0;

/***************** Initialisierungen durchführen ******************/

void
initialize()
{
	/* char c; */
	/* char filename[256]; */

	/* cout <<"\nName der Eingabedatei eingeben--> "; */
	/* cin >> filename; */

	/* Eingabefile öffnen*/
	fin.open("testprog1.tst", ios::in);

	/* cout << "\nName der Ausgabedatei eingeben--> "; */
	/* filename = ; */
	/* cin >> filename; */

	/* Ausgabedatei öffnen */
	fout.open("stdout.out", ios::out);
	// fout.open("out.txt", ios::out);
	fout << "***************** Ausgabe ***************\n";

	/* cout << "\nName der Fehlerdatei eingeben-->"; */
	/* filename = "err.TEST"; */
	/* cin >> filename; */

	/* Fehlerdatei öffnen */
	ferr.open("error.out", ios::out);
	// ferr.open("err.txt",ios::out);

	ferr << "**************** Fehlermeldungen*************\n";

	/* cout << "\nTrace gewünscht ? (y/n): "; */
	/* cin >> c; */
	/* if (c == 'y') { /1* Datei für Trace  öffnen *1/ */
		trace.open("trace.out", ios::out);
		tracesw = TRUE;
	/* } else { */
	/* 	tracesw = FALSE; */
	/* } */

	/* Datei für Symboltabellenausgabe öffnen */
	fsym.open("table.out", ios::out);
	fsym << "**************** Symboltabellen*************\n";

	/* Initialisieren des Scanners */
	initlexan();
}

/************ Endebehandlung bei fehlerfreier Übersetzung *****/
/* zur Zeit nur Ausgabe der Symboltabelle */

void
stop()
{
	/* Symboltabellen ausgeben */
	printsymtab(firstsym);
}
