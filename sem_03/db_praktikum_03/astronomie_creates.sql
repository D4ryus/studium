CREATE TABLE Uni (
	uname char(20),
	gruendungsdatum date,
	Primary Key(UName)
);

CREATE TABLE Fernrohr(
	kennziffer int,
	brennweite int,
	uniname char(20) not null,
	kaufdatum date,
	Primary Key(Kennziffer),
	foreign key (uniname) references Uni
);

CREATE TABLE Projekt(
	pname char(20),
	abgabetermin date,
	fernrohr_kz int not null,
	Primary Key(pname),
	Unique (fernrohr_kz),
	Foreign Key(fernrohr_kz) References Fernrohr
);

CREATE TABLE Forscher(
	fname char(20),
	alter int,
	uniname char(20),
	einstelldatum date,
	projektname char(20),
	wochenarbeitszeit int,
	Primary Key(fname),
	Foreign Key(projektname) References Projekt,
	Foreign Key(uniname) References Uni
);

CREATE TABLE Zeitschrift(
	zname char(20),
	auflage int,
	Primary Key(zname)
);

CREATE TABLE Artikel(
	titel char(20),
	laenge int,
	zeitschrname char(20) not null,
	veroeffdatum date,
	Primary Key(titel),
	Foreign Key(zeitschrname) References Zeitschrift
);


create table schreibt (
	forschername char(20),
	artikelname char(20),
	status int,
	primary key (forschername, artikelname),
	foreign key (forschername) references Forscher,
	foreign key (artikelname) references Artikel
);

create table gibt_heraus (
	forschername char(20),
	zeitschrname char(20),
	amtsperiode int,
	primary key (forschername, zeitschrname),
	foreign key (forschername) references Forscher,
	foreign key (zeitschrname) references Zeitschrift
);
