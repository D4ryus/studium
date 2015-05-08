/******************************** init.cxx ************************/



/* Initialisierungen für Compiler PL0  */
#ifndef GLOBAL_H
#include "global.h"
#endif


ifstream fin;					/* Zu übersetzende Eingaben */
ofstream fout,					/* Ausgabedatei */
	ferr,					/* Fehlerausgaben */
	fsym,					/* Ausgabe für Symboltabelle */
	trace;					/* Ausgabe für Trace */



int tracesw;
int level=0;

/***************** Initialisierungen durchführen ******************/

void initialize()
{
	char c;
	char filename[20];


	cout <<"\n Name der Eingabedatei eingeben-->";
	cin >> filename;

	/* Eingabefile öffnen*/
	fin.open(filename, ios::in);



	cout << "\n Name der Ausgabedatei eingeben-->";
	cin >> filename;

	/* Ausgabedatei öffnen */
	fout.open(filename,ios::out);
	// fout.open("out.txt",ios::out);
	fout<<"\n\n***************** Ausgabe ***************\n";




	cout<<"\n Name der Fehlerdatei eingeben-->";
	cin >>  filename;

	/* Fehlerdatei öffnen */
	ferr.open(filename,ios::out);
//  ferr.open("err.txt",ios::out);

	ferr<<"\n\n**************** Fehlermeldungen*************\n";



	cout<<"\n Trace gewünscht ? (y/n): ";
	cin>> c;
	if ( c == 'y')
	{ /* Datei für Trace  öffnen */
		trace.open("trace.out",ios::out);
		tracesw = TRUE;
	}
	else tracesw = FALSE;



	/* Datei für Symboltabellenausgabe öffnen */
	fsym.open("table.out",ios::out);
	fsym<<"\n\n**************** Symboltabellen*************\n";



	/* Initialisieren des Scanners */
	initlexan();


}



/************ Endebehandlung bei fehlerfreier Übersetzung  *****/
/* zur Zeit nur Ausgabe der Symboltabelle */


void stop()

{ /* Symboltabellen ausgeben  */

	printsymtab(firstsym);

}




