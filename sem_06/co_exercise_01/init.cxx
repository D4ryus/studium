/******************************** init.cxx ************************/

/* Initialisierungen f�r Compiler PL0  */
#ifndef GLOBAL_H
#include "global.h"
#endif
#include <stdio.h>

ifstream fin;   /* Zu �bersetzende Eingaben */
ofstream fout,  /* Ausgabedatei */
	 ferr,  /* Fehlerausgaben */
	 fsym,  /* Ausgabe f�r Symboltabelle */
	 trace; /* Ausgabe f�r Trace */

int tracesw;
int level = 0;

/***************** Initialisierungen durchf�hren ******************/

void
initialize()
{
	/* char c; */
	/* char filename[256]; */

	/* cout <<"\nName der Eingabedatei eingeben--> "; */
	/* cin >> filename; */

	/* Eingabefile �ffnen*/
	fin.open("testprog1.tst", ios::in);

	/* cout << "\nName der Ausgabedatei eingeben--> "; */
	/* filename = ; */
	/* cin >> filename; */

	/* Ausgabedatei �ffnen */
	fout.open("stdout.out", ios::out);
	// fout.open("out.txt", ios::out);
	fout << "***************** Ausgabe ***************\n";

	/* cout << "\nName der Fehlerdatei eingeben-->"; */
	/* filename = "err.TEST"; */
	/* cin >> filename; */

	/* Fehlerdatei �ffnen */
	ferr.open("error.out", ios::out);
	// ferr.open("err.txt",ios::out);

	ferr << "**************** Fehlermeldungen*************\n";

	/* cout << "\nTrace gew�nscht ? (y/n): "; */
	/* cin >> c; */
	/* if (c == 'y') { /1* Datei f�r Trace  �ffnen *1/ */
		trace.open("trace.out", ios::out);
		tracesw = TRUE;
	/* } else { */
	/* 	tracesw = FALSE; */
	/* } */

	/* Datei f�r Symboltabellenausgabe �ffnen */
	fsym.open("table.out", ios::out);
	fsym << "**************** Symboltabellen*************\n";

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
