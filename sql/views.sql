
CREATE OR REPLACE VIEW prj.OutKierunek AS
SELECT ki.id_kierunek AS ID,
	ki.nazwa,
	ki.liczba_miejsc AS miejsca,
	ki.dlugosc,
	ki.stopien,
	wy.skrot_nazwy AS wydzial,
	COUNT(pk.id_przedmiot) AS przedmioty,
	COUNT(sk.nr_albumu) AS studenci
FROM prj.kierunek KI
FULL JOIN prj.wydzial_kierunek WK USING (id_kierunek)
LEFT JOIN prj.wydzial WY USING (id_wydzial)
FULL JOIN prj.przedmiot_kierunek PK USING (id_kierunek)
FULL JOIN prj.student_kierunek SK USING (id_kierunek)
GROUP BY 1, 2, 3, 4, 5, 6
ORDER BY 1;

CREATE OR REPLACE VIEW prj.OutProwadzacy AS
SELECT pr.id_prowadzacy AS ID,
	pr.imie,
	pr.drugie_imie AS "drugie imie",
	pr.nazwisko,
	pr.email,
	wy.skrot_nazwy AS wydzial,
	pz.nazwa AS przedmiot
FROM prj.prowadzacy PR
FULL JOIN prj.wydzial_prowadzacy WP USING (id_prowadzacy)
LEFT JOIN prj.wydzial WY USING (id_wydzial)
FULL JOIN prj.prowadzacy_przedmiot PP USING (id_prowadzacy)
LEFT JOIN prj.przedmiot PZ USING (id_przedmiot)
ORDER BY 1;

CREATE OR REPLACE VIEW prj.OutPrzedmiot AS
SELECT id_przedmiot AS ID,
	pr.nazwa,
	semestr,
	liczba_ects AS ECTS,
	miejsca,
	egzamin,
	typ,
	opis,
	ki.skrot_nazwy AS kierunek
FROM prj.przedmiot PR
FULL JOIN prj.przedmiot_kierunek USING (id_przedmiot)
JOIN prj.kierunek KI USING (id_kierunek)
ORDER BY 1;

CREATE OR REPLACE VIEW prj.OutStudent AS
SELECT nr_albumu AS "nr albumu",
	imie,
	drugie_imie AS "drugie imie",
	nazwisko,
	email,
	data_urodzenia AS "data urodzenia",
	miejsce_zamieszkania AS miejscowosc,
	plec,
	data_rozpoczecia AS rozpoczecie,
	ki.skrot_nazwy AS kierunek,
	ki.stopien,
	wy.skrot_nazwy AS wydzial
FROM prj.student
FULL JOIN prj.student_informacje USING (nr_albumu)
LEFT JOIN prj.student_kierunek USING (nr_albumu)
LEFT JOIN prj.kierunek KI USING (id_kierunek)
JOIN prj.wydzial_kierunek USING (id_kierunek)
JOIN prj.wydzial WY USING (id_wydzial)
ORDER BY 1;

CREATE OR REPLACE VIEW prj.OutWydzial AS
SELECT id_wydzial AS ID,
	nazwa,
	skrot_nazwy AS skrot,
	(SELECT COUNT(id_kierunek)
		FROM prj.wydzial_kierunek WK
		WHERE wk.id_wydzial = wy.id_wydzial)
		AS kierunki,
	(SELECT COUNT(id_prowadzacy)
		FROM prj.wydzial_prowadzacy WP
		WHERE wp.id_wydzial = wy.id_wydzial)
		AS prowadzacy
FROM prj.wydzial WY
GROUP BY 1, 2, 3
ORDER BY 1;

CREATE OR REPLACE VIEW prj.PrzedmiotBezProw AS
SELECT id_przedmiot,
	nazwa,
	semestr
FROM prj.przedmiot
EXCEPT
SELECT id_przedmiot,
	nazwa,
	semestr
FROM prj.prowadzacy_przedmiot
JOIN prj.przedmiot USING (id_przedmiot)
ORDER BY 1;

CREATE OR REPLACE VIEW prj.ProwadzacyBezPrzed AS
SELECT id_prowadzacy,
	imie,
	nazwisko
FROM prj.prowadzacy
EXCEPT
SELECT id_prowadzacy,
	imie,
	nazwisko
FROM prj.prowadzacy_przedmiot
JOIN prj.prowadzacy USING (id_prowadzacy)
ORDER BY 1;

CREATE OR REPLACE VIEW prj.LastPrzedmiot AS
SELECT DISTINCT ON (id_przedmiot) id_przedmiot
	FROM prj.przedmiot
	ORDER BY 1 DESC
	LIMIT 1;

CREATE OR REPLACE VIEW prj.LastProwadzacy AS
SELECT DISTINCT ON (id_prowadzacy) id_prowadzacy
	FROM prj.prowadzacy
	ORDER BY 1 DESC
	LIMIT 1;

CREATE OR REPLACE VIEW prj.LastKierunek AS
SELECT DISTINCT ON (id_kierunek) id_kierunek
	FROM prj.kierunek
	ORDER BY 1 DESC
	LIMIT 1;

CREATE OR REPLACE VIEW prj.LastWydzial AS
SELECT DISTINCT ON (id_wydzial) id_wydzial
	FROM prj.wydzial
	ORDER BY 1 DESC
	LIMIT 1;

CREATE OR REPLACE VIEW prj.LastStudent AS
SELECT DISTINCT ON (nr_albumu) nr_albumu
	FROM prj.student
	ORDER BY 1 DESC
	LIMIT 1;

CREATE OR REPLACE VIEW prj.OutPrzedObieralne AS
SELECT *
FROM prj.OutPrzedmiot OW
WHERE ow.typ = 'obieralny'
ORDER BY 1;
