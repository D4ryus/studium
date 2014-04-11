INSERT INTO Agent VALUES ('Max Mustermann',	'Dorfweg 3');
INSERT INTO Agent VALUES ('Georg Meier',	'Pflaumenstr. 3');

INSERT INTO Songwriter VALUES ('Franz Obermeier',	'Landshuterstr. 23');
INSERT INTO Songwriter VALUES ('Josef Huber', 		'Niedermeierstr. 15');

INSERT INTO Popstar VALUES ('Falco',	'Max Mustermann');
INSERT INTO Popstar VALUES ('Elvis',	'Max Mustermann');
INSERT INTO Popstar VALUES ('John B.',	'Georg Meier');
INSERT INTO Popstar VALUES ('Jackson',	'Georg Meier');

INSERT INTO Lied VALUES ('Hello World',		1,		'Franz Obermeier',	1981);
INSERT INTO Lied VALUES ('Second Time',		12,		'Josef Huber',		2005);
INSERT INTO Lied VALUES ('The Best',		10,		'Franz Obermeier',	1991);

INSERT INTO Instrument VALUES ('Gitarre',	'Git/Bass');
INSERT INTO Instrument VALUES ('Schlagzeug',	'Drums');
INSERT INTO Instrument VALUES ('Bass',		'Git/Bass');

INSERT INTO Musiker VALUES ('Crazy Joe',	'Elvis',	'Gitarre',		5000.00);
INSERT INTO Musiker VALUES ('Crazy Mike',	'Elvis',	'Bass',			4500.00);
INSERT INTO Musiker VALUES ('Crazy Tony',	'Elvis',	'Schlagzeug',		3762.34);
INSERT INTO Musiker VALUES ('Funky Pete',	'Falco',	'Gitarre',		8000.00);
INSERT INTO Musiker VALUES ('Fresh Prinz',	'John B.',	'Bass',			3600.50);

INSERT INTO singt VALUES ('Hello World',	'Elvis',	'Crazy Show');
INSERT INTO singt VALUES ('Second Time',	'Elvis',	'Crazy Show');
INSERT INTO singt VALUES ('The Best',		'Falco',	'The One and Only');
INSERT INTO singt VALUES ('Second Time',	'John B.',	'The One and Only');
INSERT INTO singt VALUES ('The Best',		'Jackson',	'Around the World');
INSERT INTO singt VALUES ('Second Time',	'Jackson',	'Around the World');

INSERT INTO setzt_ein VALUES ('Hello World',	'Gitarre');
INSERT INTO setzt_ein VALUES ('Hello World',	'Bass');
INSERT INTO setzt_ein VALUES ('Second Time',	'Schlagzeug');
INSERT INTO setzt_ein VALUES ('Second Time',	'Bass');
INSERT INTO setzt_ein VALUES ('The Best',	'Schlagzeug');
INSERT INTO setzt_ein VALUES ('The Best',	'Bass');
