insert into Uni Values ('Uni Passau', '1917-5-13');
insert into Uni Values ('TU Muenchen', '1894-5-2');
insert into Uni Values ('FH Landshut', '1970-9-3');
insert into Uni Values ('FH Deggendorf', '1988-11-3');
insert into Uni Values ('FH Rosenheim', '1977-1-23');



insert into Fernrohr Values (1, 100, 'TU Muenchen', '2003-11-30');
insert into Fernrohr Values (2, 500, 'FH Landshut', '2000-8-4');
insert into Fernrohr Values (3, 200, 'Uni Passau', '2001-10-22');
insert into Fernrohr Values (4, 1000, 'TU Muenchen', '2000-3-14');
insert into Fernrohr Values (5, 550, 'TU Muenchen', '2005-1-18');
insert into Fernrohr Values (6, 50, 'Uni Passau', '2002-3-29');
insert into Fernrohr Values (7, 750, 'FH Deggendorf', '2000-2-5');
insert into Fernrohr Values (8, 900, 'FH Landshut', '2001-11-22');
insert into Fernrohr Values (9, 150, 'FH Landshut', '2004-6-10');



insert into Projekt Values('Mond', '2003-10-10', 1);
insert into Projekt Values('Milchstrasse', '2004-11-1', 3);
insert into Projekt Values('Kometen', '2003-5-6', 2);
insert into Projekt Values('Pulsare', '2003-2-10', 6);
insert into Projekt Values('Hubble', '2006-2-15', 5);
insert into Projekt Values('Jupiter', '2007-12-31', 9);
insert into Projekt Values('Centauri', '2003-8-31', 4);
insert into Projekt Values('Pluto', '2003-2-28', 8);
insert into Projekt Values('Sonne', '2010-1-15', 7);



insert into Forscher Values('Galilei', 34, 'TU Muenchen', '1996-02-23', 'Mond', 40);
insert into Forscher Values('Newton', 56, 'FH Landshut', '1965-03-11', 'Kometen', 15);
insert into Forscher Values('Einstein', 23, 'FH Rosenheim', '1943-07-04', 'Jupiter', 5);
insert into Forscher Values('Nernst', 23, 'FH Landshut', '1999-08-01', 'Sonne', 21);
insert into Forscher Values('Sommerfeld', 10, 'Uni Passau', '2000-12-09', 'Sonne', 15);
insert into Forscher Values('Planck', 37, 'TU Muenchen', '1988-11-15', 'Milchstrasse', 30);
insert into Forscher Values('Sandage', 42, 'FH Rosenheim', '1995-02-25', 'Centauri', 3);
insert into Forscher Values('Leibnitz', 70, 'FH Landshut', '1980-04-11', 'Hubble', 8);
insert into Forscher Values('Cassini', 91, 'TU Muenchen', '1980-04-30', 'Jupiter', 35);
insert into Forscher Values('Kepler', 66, 'TU Muenchen', '1977-11-01', 'Pluto', 19);
insert into Forscher Values('Herschel', 50, 'FH Deggendorf', '1974-09-15', 'Sonne', 20);
insert into Forscher Values('Erasmus', 84,  'FH Deggendorf', '1969-03-03', 'Kometen', 5);
insert into Forscher Values('Gauss', 66,  'Uni Passau', '2002-02-07', 'Pulsare', 6);
insert into Forscher Values('Lavoisier', 30, 'TU Muenchen', '2000-04-27', 'Milchstrasse', 25);
insert into Forscher Values('Baade', 22, 'Uni Passau', '1991-02-22', 'Centauri', 10);



insert into Zeitschrift Values ('Sky and Telescope', 500000);
insert into Zeitschrift Values ('Astronomiezeit', 800);
insert into Zeitschrift Values ('Ikarus', 500);
insert into Zeitschrift Values ('Sonnenkurier', 3200);
insert into Zeitschrift Values ('Planetenmagazin', 400000);



insert into Artikel Values('Galaxienkollisionen', 5, 'Sky and Telescope', '2000-10-22');
insert into Artikel Values('Sternenstaub', 12, 'Planetenmagazin', '2004-1-21');
insert into Artikel Values('Sonnenflecken', 25, 'Ikarus', '2005-4-3');
insert into Artikel Values('Bahnexzentrizitaet', 2, 'Ikarus', '2002-5-12');
insert into Artikel Values('Magellanische Wolken', 33, 'Astronomiezeit', '2001-12-7');
insert into Artikel Values('extrasolare Planeten', 6, 'Sky and Telescope', '2002-9-23');
insert into Artikel Values('dunkle Materie', 1, 'Sonnenkurier', '2000-8-27');
insert into Artikel Values('Energiebilanz', 10, 'Planetenmagazin', '2000-2-1');
insert into Artikel Values('Urknall', 8, 'Sonnenkurier', '2006-4-28');
insert into Artikel Values('Jupitermission', 20, 'Sky and Telescope', '2004-7-17');



insert into schreibt Values('Galilei', 'Energiebilanz', 0);
insert into schreibt Values('Sommerfeld', 'extrasolare Planeten', 3);
insert into schreibt Values('Cassini',  'Magellanische Wolken', 2);
insert into schreibt Values('Gauss',  'Sternenstaub', 0);
insert into schreibt Values('Erasmus',  'Urknall', 1);
insert into schreibt Values('Einstein', 'Galaxienkollisionen', 2);
insert into schreibt Values('Kepler',  'Galaxienkollisionen', 0);
insert into schreibt Values('Galilei', 'extrasolare Planeten', 4);
insert into schreibt Values('Erasmus',  'Sonnenflecken', 2);
insert into schreibt Values('Galilei',  'Urknall', 3);
insert into schreibt Values('Galilei', 'Galaxienkollisionen', 1);
insert into schreibt Values('Leibnitz', 'extrasolare Planeten', 0);
insert into schreibt Values('Cassini',  'Jupitermission', 3);
insert into schreibt Values('Gauss',  'Jupitermission', 4);
insert into schreibt Values('Erasmus',  'Energiebilanz', 2);
insert into schreibt Values('Einstein', 'Magellanische Wolken', 3);
insert into schreibt Values('Kepler',  'Sonnenflecken', 1);
insert into schreibt Values('Galilei', 'Sternenstaub', 2);
insert into schreibt Values('Erasmus',  'Sternenstaub', 4);
insert into schreibt Values('Galilei',  'dunkle Materie', 0);
insert into schreibt Values('Sandage', 'Sternenstaub', 2);
insert into schreibt Values('Sommerfeld', 'Energiebilanz', 1);
insert into schreibt Values('Cassini',  'Urknall', 3);
insert into schreibt Values('Sandage',  'Sonnenflecken', 3);
insert into schreibt Values('Sommerfeld',  'Urknall', 2);
insert into schreibt Values('Einstein', 'dunkle Materie', 1);
insert into schreibt Values('Kepler',  'Sternenstaub', 0);
insert into schreibt Values('Leibnitz', 'Urknall', 0);
insert into schreibt Values('Erasmus',  'Galaxienkollisionen', 0);
insert into schreibt Values('Sommerfeld',  'dunkle Materie', 4);



insert into gibt_heraus Values ('Galilei', 'Ikarus', 3);
insert into gibt_heraus Values ('Erasmus', 'Sky and Telescope', 5);
insert into gibt_heraus Values ('Cassini', 'Astronomiezeit', 12);
insert into gibt_heraus Values ('Erasmus', 'Ikarus', 3);
insert into gibt_heraus Values ('Sandage', 'Sky and Telescope', 5);
insert into gibt_heraus Values ('Einstein', 'Sonnenkurier', 10);
insert into gibt_heraus Values ('Nernst', 'Planetenmagazin', 6);
insert into gibt_heraus Values ('Kepler', 'Sky and Telescope', 5);
insert into gibt_heraus Values ('Kepler', 'Astronomiezeit', 1);
insert into gibt_heraus Values ('Sommerfeld', 'Ikarus', 7);
insert into gibt_heraus Values ('Sommerfeld', 'Sky and Telescope', 4);
insert into gibt_heraus Values ('Gauss', 'Sonnenkurier', 5);

