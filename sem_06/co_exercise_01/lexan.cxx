/************************ lexan.cxx  04.04. 2013 ********************/
/*************** Scanner *******************************/


#ifndef GLOBAL_H 
#include "global.h"
#endif 



#define NORW   12   		/* Zahl der reservierten Worte */ 

#define RWSYMLEN  15		/* Max. L�nge reservierter Symbole */ 






int lineno;					/* Zeilennummer */                            		

int num ;                  	/* Wert einer int-Konstanten  */
double realnum; 			/* Wert einer real-Konstanten*/ 

char idname[BSIZE];      /* Name eines Bezeichners ;
							wird vom Parser weiterverwendet */ 


char actchar;                /* gelesenes Zeichen */ 
                      



/*  Um Bezeichner vor reservierten Symbolene unterscheiden zu k�nnen,
wird eine Tabelle reservierte Worte verwendet (restable). 

Die Tabelle enth�lt Eintr�ge f�r jedes Schl�sselwort, bestehend aus 
dem Schl�sselwort selbst und dem zugeh�rigen Tokentyp (Codierung vgl.global.h):

Bei Erkennen eines m�glichen Bezeichners wird zuerst die Tabelle
der reservierten Symbole durchsucht (lookforres); 
wird ein Schl�sselwort gefunden, liefert lookforres den dem Schl�sselwort 
zugeordneten Tokentyp; sonst 0. Bei Ergebnis 0 liegt dann tats�chlich ein
Bezeichner vor. 
*/ 




/* Struktur eines Eintrags in der Tabelle reservierter Symbole */ 


struct ressw 

{ char ressymbol [RWSYMLEN];			/* Symbol */             
  int token;							/* zugeh�riger Tokentyp */ 
} ;



/* Tabelle reservierter Worte */ 


struct ressw 
			restable [] =  
				{	"const", CONST,
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
					"real", REAL
				};





/* Suchen nach einem reservierten Symbol */ 


int lookforres( char *s)

/* Sucht in Tabelle reservierter Worte nach s und liefert zugeh�rigen Token
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

{ num = NONE;						
  realnum = -0.0; 
  idname [0] = NULL;					
  lineno = 1;
  fin.get(actchar);			/* Erstes Zeichen der Eingabe lesen */  
    
}    







/********** Funktion nextsymbol ************************************************/ 
/***********zentrale Funktion zum Lesen des 
			n�chsten lexikalischen Symbols ******************************/ 

			
/* identifiziert n�chstes lexikalisches Symbol der Eingabe ;
bei Aufruf muss sich das n�chste Eingabezeichen in actchar befinden, 

*/ 

/**    liefert Codierung in Variable token: 

		- Konstante:				token == INTNUM und Wert der Konstanten in Variable num
							token == REALNUM und Wert in realnum
		- Bezeichner:				token == ID  und Zeiger auf Name in idname 
		- Schl�sselwort:			token == Tokentyp des resevierten Symbols nach 
									Suche in restable 
		- Operatoren,Sonderzeichen :entsprechende Token 

**/ 
										



int nextsymbol () 

{
	int token;  
	char lexbuf[BSIZE] ;		/* Puffer f�r Eingabezeichen */ 	


	while( !fin.eof())				/* Eingabe-Dateiende nicht erreicht */ 
	{ 

		if ( actchar== ' ' || actchar== '\t')
			/*Blank und Tab in Ausgabedatei kopieren und entfernen */ 
			{	fout.put(actchar);
				fin.get(actchar);
				
		     }


		else if (actchar== '\n' ||  actchar == '\r')  
			/* Newline in Ausgabedatei kopieren, entfernen, Zeilennummer erh�hen */ 
			{ fout.put(actchar);
			  fin.get(actchar);
			  lineno++;
			  }


		else if (isdigit(actchar))

				{ /***** actchar ist Ziffer --> Konstanten erkennen  *****/
					
					char zahl [BSIZE];		/* Puffer f�r Ziffern */ 
					int b = 0;			/* Zeichenzahl*/ 


					/* reg. Ausdruck    (digit)+ '.' (digit)+   erkennen ==>
					   solange Ziffern vorhanden --> Konstante */ 



				

					 
				




					
				}


		else if (isalpha(actchar))
				/***** actchar ist Buchstabe -->  Identifikatoren erkennen ****/
				{	
					
			
					int b = 0 ;				/* Zeichenzahl */ 

					/* reg. Ausdruck   letter (letter|digit)*  erkennen ==>
					    solange Buchstaben oder Ziffern folgen --> Identifikator */ 

					






				}

		
		

		else    /***** Sonderzeichen oder Operatoren erkennen ***************/ 







				
		

	
 	}/* end while */ 


 	return(DONE); 	/* EIngabe -Ende erreicht */ 
		
}


