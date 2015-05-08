
/****************** lexmain.cxx *********************/

/* Hauptprogramm zum Test der lexikalischen Analyse */ 
/****************************************************/


#ifndef GLOBAL_H 
#include "global.h"
#endif 






int main()
{
	int lookahead = -1; 

	/* Initialisierungen durchführen */
	initialize(); 

	/* Symbole aus Eingabedatei lesen bis Dateiende */ 
  lookahead = nextsymbol();
  fout << "		Tokentyp=    " <<lookahead; 
  
 
  while (lookahead != DONE)
	{ 	
		lookahead = nextsymbol();
		fout << "		Tokentyp=    " <<lookahead; 

 	}

	exit(0); 	/* Erfolg */
}


  

 



