CREATE TABLE Agent (
	AName 				CHAR(20),
	AAdresse			CHAR(20),

	PRIMARY KEY (AName));


CREATE TABLE Songwriter (
	SName 				CHAR(20),
	SAdresse 			CHAR(20),

	PRIMARY KEY (SName));


CREATE TABLE Instrument (
	IName 				CHAR(10),
	Sparte 				CHAR(10),

	PRIMARY KEY (IName));


CREATE TABLE Popstar (
	PName 				CHAR(20),
	Agentenname 			CHAR(20),

	PRIMARY KEY (PName),

	FOREIGN KEY (Agentenname) 	REFERENCES Agent);


CREATE TABLE Musiker (
	MName 				CHAR(20),
	Popstarname 			CHAR(20),
	Instrumentenname 		CHAR(10) NOT NULL,
	Gehalt 				DECIMAL(10,2),

	PRIMARY KEY (MName),

	FOREIGN KEY (Popstarname) 	REFERENCES Popstar,
	FOREIGN KEY (Instrumentenname) 	REFERENCES Instrument);


CREATE TABLE Lied (
	Titel 				CHAR(20),
	Strophenzahl 			INT,
	Writername 			CHAR(20) NOT NULL,
	Kompositionsjahr 		INT,

	PRIMARY KEY (Titel),

	FOREIGN KEY (Writername) 	REFERENCES Songwriter);


CREATE TABLE singt (
	Titel 				CHAR(20),
	Popstarname 			CHAR(20),
	in_Konzert 			CHAR(20),

	PRIMARY KEY (Titel, Popstarname)

	FOREIGN KEY (Titel) 		REFERENCES Lied,
	FOREIGN KEY (Popstarname) 	REFERENCES Popstar);


CREATE TABLE setzt_ein (
	Titel 				CHAR(20),
	Instrumentenname 		CHAR(10),

	PRIMARY KEY (Titel, Instrumentname)

	FOREIGN KEY (Titel) 		REFERENCES Lied,
	FOREIGN KEY (Instrumentenname) 	REFERENCES Instrument);
