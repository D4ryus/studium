--1
select distinct tn
from lieferant join lpt on lpt.ln = lieferant.lnummer
where stadt = 'Landshut';

select distinct tn
from lieferant, lpt
where lpt.ln = lieferant.lnummer and stadt = 'Landshut';

select distinct tn
from lpt
where ln in (select lnummer
                from lieferant
                where stadt = 'Landshut');

--2
select distinct tname
from teil
where tnummer = any(select tn
                    from lpt
                    group by tn
                    having avg(menge) > 1000);

--3
select projekt.stadt
from projekt
union
select lieferant.stadt
from lieferant;

--4
select lname
from lieferant
where jahreink > any (select jahreink
                    from lieferant
                    where lname = 'Zymi')
order by lname desc;

--5
select lname
from lieferant
where stadt > 'Landshut'
order by lname asc;

select lname
from lieferant
where stadt > all (select stadt
                    from projekt);

select lname
from lieferant
where stadt > all (select projekt.stadt
                    from lieferant join projekt on lieferant.stadt = projekt.stadt);

--6
select pname
from projekt
where budget < any (select jahreink
                    from lieferant)
order by pname asc;

select pname
from projekt
where budget <  (select Min(jahreink)
                    from lieferant)
order by pname asc;

--7
select distinct teil.tname
from teil, lieferant, projekt, lpt
where teil.tnummer = (select teil.tnummer from teil except (select lpt.tn 
                                                            from lpt join lieferant on lpt.ln = lieferant.lnummer union select lpt.tn
                                                                                                                        from lpt join projekt on lpt.pn = projekt.pnummer));

select distinct teil.tname
from teil
where teil.tnummer not in (select lpt.tn
                           from lpt, projekt, lieferant
                           where lpt.ln = lieferant.lnummer and lpt.pn = projekt.pnummer);

select distinct teil.tname
from teil
where not exists (select lpt.tn
                  from lpt, projekt, lieferant
                  where lpt.ln = lieferant.lnummer and lpt.pn = projekt.pnummer);

--8
select distinct lpt.tn, teil.gewicht, teil.farbe, max(lpt.menge)
from teil inner join lpt on teil.tnummer = lpt.tn
where teil.farbe = 'red' or teil.farbe = 'yellow' and lpt.tn in (select lpt.tn
                                                                 from lpt
                                                                 group by lpt.tn
                                                                 having sum(menge) > 10)
group by lpt.tn, teil.gewicht, teil.farbe
order by lpt.tn;

--9
create table newlpt(
    newln integer NOT NULL,
    newtn integer NOT NULL,
    newpn integer NOT NULL,
    primary key (newln, newtn, newpn),
    foreign key (newln) references lieferant(lnummer),
    foreign key (newtn) references teile(tnummer),
    foreign key (newpn) references projekt(pnummer),
    );

    insert into newlpt
    select lpt.ln, lpt.tn, lpt.pn
    from lpt
    where lpt.pn = 3;

--10
update teil
set stadt = (select lieferant.stadt
            from lieferant
            where lname = 'Jones');

--11
delete from lpt
where ln in (select lnummer 
            from lieferant
            where stadt = 'Landshut');

--12
--Nein da lpt.ln ein foreign key ist der auf lieferant.lnummer referenziert.
