--1
select * from Projekt;

--2
select pname
from projekt
where abgabetermin < '2004-01-01';

--3
select fname, uniname
from forscher
where wochenarbeitszeit between '10' and '30';

--4
select fname, uniname, gruendungsdatum
from forscher inner join Uni on Forscher.uniname = Uni.uname
where wochenarbeitszeit between '10' and '30';

--5
select *
from zeitschrift
where zname = 'Sky and Telescope';

--6
select max(alter) 
from forscher 
where uniname = 'TU Muenchen';

select fname, alter
from Forscher
where alter = (select max(alter) from forscher) and uniname = 'TU Muenchen';

--7
select forschername, artikelname
from schreibt
where forschername = any (select fname from forscher where uniname = 'TU Muenchen');

select forschername, artikelname
from schreibt inner join forscher on forscher.fname = schreibt.forschername
where uniname = 'TU Muenchen';

--8
select forschername, zeitschrname
from schreibt, Artikel
where artikelname = titel;

--9
select forschername, alter, zeitschrname, auflage
from Forscher, schreibt, Artikel, Zeitschrift
where fname = forschername and artikelname = titel and zeitschrname = zname;

--10
select forschername, zeitschrname, titel
from artikel inner join schreibt on artikel.titel= schreibt.artikelname
where zeitschrname = 'Astronomiezeit' 
or zeitschrname = 'Sky and Telescope';

--11
select pname, projektname, abgabetermin, auflage
from Projekt, Forscher, gibt_heraus, Zeitschrift
where pname = projektname and fname = forschername and zeitschrname = zname;

--12
select kennziffer
from Fernrohr, Uni
where uniname = uname and gruendungsdatum < '01-01-1940';

select kennziffer
from Fernrohr join Uni on Fernrohr.uniname = Uni.uname
where gruendungsdatum < '01-01-1940';

--13
select fname
from Forscher
where fname not in (select forschername from gibt_heraus);

select Distinct fname
from Forscher
where not exists (select * from gibt_heraus where fname = forschername);

select fname
from Forscher
except select forschername
from gibt_heraus;

--14
select zeitschrname, avg(laenge)
from Artikel
group by zeitschrname;

--15
select zeitschrname, avg(laenge)
from Artikel, Zeitschrift
where auflage > 10000 and zeitschrname = zname
group by zeitschrname;

--16
select titel, forschername
from Artikel, schreibt
where titel = artikelname and zeitschrname = 'Sky and Telescope';

--17
select uniname, count(fname)
from Forscher
group by uniname
having count(fname) > 2;

--18
select zeitschrname, avg(laenge)
from Artikel
group by zeitschrname
having avg(laenge) > 10;

--19
select titel
from Artikel
where zeitschrname = any(	select zeitschrname
				from Artikel
				group by zeitschrname
				having avg(laenge) > 10
			);

--20
select distinct forschername
from schreibt
where artikelname = any (
	select titel
	from Artikel
	where zeitschrname = any (
		select zeitschrname
		from Artikel
		group by zeitschrname
		having avg(laenge) > 10)
	);
