
CREATE OR REPLACE FUNCTION prj.walidujEmailStudenta()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT 1 FROM prj.student WHERE email = NEW.email) THEN
        RETURN NEW;
    ELSE
        RAISE EXCEPTION 'Istnieje juz pozycja z identycznym adresem email.';
    END IF;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujEmailStudentaTrigger
BEFORE INSERT OR UPDATE ON prj.student
FOR EACH ROW EXECUTE PROCEDURE prj.walidujEmailStudenta();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujEmailProwadzacego()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT 1 FROM prj.prowadzacy WHERE email = NEW.email) THEN
        RETURN NEW;
    ELSE
        RAISE EXCEPTION 'Istnieje juz pozycja z identycznym adresem email.';
    END IF;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujEmailProwadzacegoTrigger
BEFORE INSERT OR UPDATE ON prj.prowadzacy
FOR EACH ROW EXECUTE PROCEDURE prj.walidujEmailProwadzacego();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujWolneMiejscaNaKierunku()
RETURNS TRIGGER AS
$$
BEGIN
    IF((SELECT COUNT(*) FROM prj.student_kierunek WHERE id_kierunek = NEW.id_kierunek)
    >= (SELECT liczba_miejsc FROM prj.kierunek WHERE id_kierunek = NEW.id_kierunek))
    THEN
        RAISE EXCEPTION 'Na tym kierunku nie ma juz wolnych miejsc.';
    ELSE
        RETURN NEW;
    END IF;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujWolneMiejscaNaKierunkuTrigger
BEFORE INSERT OR UPDATE ON prj.student_kierunek
FOR EACH ROW EXECUTE PROCEDURE prj.walidujWolneMiejscaNaKierunku();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujWolneMiejscaNaPrzedmiocie()
RETURNS TRIGGER AS
$$
BEGIN
    IF((SELECT COUNT(*) FROM prj.student_przedmiot WHERE id_przedmiot = NEW.id_przedmiot)
    >= (SELECT liczba_miejsc FROM prj.przedmiot WHERE id_przedmiot = NEW.id_przedmiot))
    THEN
        RAISE EXCEPTION 'Na tym przedmiocie nie ma juz wolnych miejsc.';
    ELSE
        RETURN NEW;
    END IF;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujWolneMiejscaNaPrzedmiocieTrigger
BEFORE INSERT OR UPDATE ON prj.student_przedmiot
FOR EACH ROW EXECUTE PROCEDURE prj.walidujWolneMiejscaNaPrzedmiocie();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowyKierunek()
RETURNS TRIGGER AS
$$
BEGIN
    IF EXISTS(SELECT *
        FROM prj.kierunek
        WHERE id_kierunek = NEW.id_kierunek
        OR skrot_nazwy = NEW.skrot_nazwy)
    THEN
        RAISE EXCEPTION 'Istnieje juz kierunek z takim samym ID lub skrotem.';
    END IF;
    IF NEW.liczba_miejsc < 10 THEN
        RAISE WARNING 'Utworzono kierunek ze zbyt niewielka (%) liczba miejsc. Wartosc ta zostala zmieniona na 100.', NEW.liczba_miejsc;
        NEW.liczba_miejsc := 100;
    END IF;
    IF NEW.dlugosc < 6 THEN
        RAISE WARNING 'Utworzono kierunek ze zbyt niska (%) liczba semestrow. Wartosc ta zostala zmieniona na 6.', NEW.dlugosc;
        NEW.dlugosc := 6;
    END IF;
    IF NEW.stopien > 2 OR NEW.stopien < 1 THEN
        RAISE WARNING 'Utworzono kierunek z niepoprawna wartoscia stopnia (%). Wartosc ta zostala zmieniona na 1.', NEW.stopien;
        NEW.stopien := 1;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowyKierunekTrigger
BEFORE INSERT OR UPDATE ON prj.kierunek
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowyKierunek();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowyKierunek_Wymagania()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT *
        FROM prj.kierunek
        WHERE NEW.id_kierunek = id_kierunek
        OR NEW.skrot_nazwy = skrot_nazwy)
    THEN
        RAISE EXCEPTION 'Nie mozna dodac wymagan do kierunku o ID = %, poniewaz taki nie istnieje.', NEW.id_kierunek;
    END IF;
    IF NEW.prog_punktowy < 0 OR NEW.prog_punktowy > 1000 THEN
        RAISE WARNING 'Wprowadzono nienaturalna wartosc progu punktowego (%). Wartosc ta zostala zmieniona na 500.', NEW.prog_punktowy;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowyKierunek_WymaganiaTrigger
BEFORE INSERT OR UPDATE ON prj.kierunek_wymagania
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowyKierunek_Wymagania();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowyWydzial()
RETURNS TRIGGER AS
$$
BEGIN
    IF EXISTS(SELECT *
        FROM prj.wydzial
        WHERE NEW.id_wydzial = id_wydzial)
    THEN
        RAISE EXCEPTION 'Istnieje juz wydzial z takim samym ID (%).', NEW.id_wydzial;
    END IF;
    IF EXISTS(SELECT *
        FROM prj.wydzial
        WHERE NEW.nazwa = nazwa)
    THEN
        RAISE EXCEPTION 'Istnieje juz wydzial o nazwie %.', NEW.nazwa;
    END IF;
    IF EXISTS(SELECT *
        FROM prj.wydzial
        WHERE NEW.skrot_nazwy = skrot_nazwy)
    THEN
        RAISE EXCEPTION 'Istnieje juz wydzial ze skrotem %', NEW.skrot_nazwy;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowyWydzialTrigger
BEFORE INSERT OR UPDATE ON prj.wydzial
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowyWydzial();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowegoProwadzacego()
RETURNS TRIGGER AS
$$
BEGIN
    IF EXISTS(SELECT *
        FROM prj.prowadzacy
        WHERE NEW.id_prowadzacy = id_prowadzacy)
    THEN
        RAISE EXCEPTION 'Istnieje juz prowadzacy o ID = %.', NEW.id_prowadzacy;
    END IF;
    IF LENGTH(NEW.imie) = 0 THEN
        RAISE WARNING 'Nie podano imienia nowego prowadzacego. Z tego wzgledu nadano mu imie Horacy.';
        NEW.imie := 'Horacy';
    END IF;
    IF LENGTH(NEW.nazwisko) = 0 THEN
        RAISE WARNING 'Nie podano nazwiska nowego prowadzacego. Z tego wzgledu nadano mu nazwisko Adamiak.';
        NEW.nazwisko := 'Adamiak';
    END IF;
    -- IF LENGTH(NEW.drugie_imie) = 0 THEN
    --     RAISE WARNING 'Nie podano drugiego imienia prowadzacego. Z tego wzgledu nadano mu drugie imie Ginter.';
    --     NEW.drugie_imie := 'Ginter';
    -- END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowegoProwadzacegoTrigger
BEFORE INSERT OR UPDATE ON prj.prowadzacy
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowegoProwadzacego();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowyWydzial_Prowadzacy()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT * FROM prj.prowadzacy WHERE NEW.id_prowadzacy = id_prowadzacy) THEN
        RAISE EXCEPTION 'Nie istnieje prowadzacy o podanym ID = %.', NEW.id_prowadzacy;
    END IF;
    IF NOT EXISTS(SELECT * FROM prj.wydzial WHERE NEW.id_wydzial = id_wydzial) THEN
        RAISE EXCEPTION 'Nie istnieje wydzial o podanym ID = %.', NEW.id_wydzial;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowyWydzial_ProwadzacyTrigger
BEFORE INSERT OR UPDATE ON prj.wydzial_prowadzacy
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowyWydzial_Prowadzacy();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowegoProwadzacego_Przedmiot()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT * FROM prj.przedmiot WHERE NEW.id_przedmiot = id_przedmiot) THEN
        RAISE EXCEPTION 'Nie istnieje przedmiot o podanym ID = %.', NEW.id_przedmiot;
    END IF;
    IF NOT EXISTS(SELECT * FROM prj.prowadzacy WHERE NEW.id_prowadzacy = id_prowadzacy) THEN
        RAISE EXCEPTION 'Nie istnieje prowadzacy o podanym ID = %.', NEW.id_prowadzacy;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowegoProwadzacego_PrzedmiotTrigger
BEFORE INSERT OR UPDATE ON prj.prowadzacy_przedmiot
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowegoProwadzacego_Przedmiot();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowyPrzedmiot()
RETURNS TRIGGER AS
$$
BEGIN
    IF EXISTS(SELECT * FROM prj.przedmiot WHERE NEW.id_przedmiot = id_przedmiot) THEN
        RAISE EXCEPTION 'Istnieje juz przedmiot o ID = %', NEW.id_przedmiot;
    END IF;
    IF LENGTH(NEW.nazwa) = 0 THEN
        RAISE EXCEPTION 'Nie podano wymaganej nazwy kierunku.';
    END IF;
    IF NEW.semestr < 1 OR NEW.semestr > 7 THEN
        RAISE WARNING 'Podano niepoprawny numer semestru. Prawidlowy zakres to <1 - 7>. Z tego wzgledu nadano wartosc 1.';
        NEW.semestr := 1;
    END IF;
    IF NEW.liczba_ects < 1 OR NEW.liczba_ects > 30 THEN
        RAISE WARNING 'Podano niepoprawna liczbe punktow ECTS. Prawidlowy zakres to <1 - 30>. Z tego wzgledu nadano wartosc 4.';
        NEW.liczba_ects := 4;
    END IF;
    IF NEW.miejsca < 10 THEN
        RAISE WARNING 'Utworzono przedmiot ze zbyt niewielka liczba miejsc (%). Wartosc ta zostala zmieniona na 100.', NEW.miejsca;
        NEW.miejsca := 100;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowyPrzedmiotTrigger
BEFORE INSERT OR UPDATE ON prj.przedmiot
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowyPrzedmiot();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowyPrzedmiot_Kierunek()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT * FROM prj.przedmiot WHERE NEW.id_przedmiot = id_przedmiot) THEN
        RAISE EXCEPTION 'Nie istnieje przedmiot o podanym ID = %', NEW.id_przedmiot;
    END IF;
    IF NOT EXISTS(SELECT * FROM prj.kierunek WHERE NEW.id_kierunek = id_kierunek OR NEW.skrot_nazwy = skrot_nazwy) THEN
        RAISE EXCEPTION 'Nie istnieje kierunek o ID = % oraz skrocie "%"', NEW.id_kierunek, NEW.skrot_nazwy;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowyPrzedmiot_KierunekTrigger
BEFORE INSERT OR UPDATE ON prj.przedmiot_kierunek
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowyPrzedmiot_Kierunek();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowyStudentPrzedmiot()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT * FROM prj.przedmiot WHERE NEW.id_przedmiot = id_przedmiot) THEN
        RAISE EXCEPTION 'Nie istnieje przedmiot o podanym ID = %', NEW.id_przedmiot;
    END IF;
    IF NOT EXISTS(SELECT * FROM prj.student WHERE NEW.nr_albumu = nr_albumu) THEN
        RAISE EXCEPTION 'Nie istnieje student o podanym numerze albumu (%).', NEW.nr_albumu;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowyStudentPrzedmiotTrigger
BEFORE INSERT OR UPDATE ON prj.student_przedmiot
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowyStudentPrzedmiot();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowaStudent_Ocena()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT *
        FROM prj.student_przedmiot
        WHERE NEW.id_przedmiot = id_przedmiot
        AND NEW.nr_albumu = nr_albumu)
    THEN
        RAISE EXCEPTION 'Student o numerze albumu % nie jest zapisany na przedmiot o ID = %.', NEW.nr_albumu, NEW.id_przedmiot;
    END IF;
    IF NEW.ocena < 2 OR NEW.ocena > 5 THEN
        RAISE EXCEPTION 'Podana wartosc oceny (%) wykracza poza zakres <2 - 5>. Nowa pozycja nie zostala zapisana.', NEW.ocena;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowaStudent_OcenaTrigger
BEFORE INSERT OR UPDATE ON prj.student_ocena
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowaStudent_Ocena();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowegoStudenta()
RETURNS TRIGGER AS
$$
BEGIN
    IF EXISTS(SELECT * FROM prj.student WHERE NEW.nr_albumu = nr_albumu) THEN
        RAISE EXCEPTION 'Istnieje juz student o podanym numerze albumu (%).', NEW.nr_albumu;
    END IF;
    IF LENGTH(NEW.imie) = 0 THEN
        RAISE WARNING 'Nie podano imienia nowego studenta. Z tego wzgledu nadano mu imie Bozydar.';
        NEW.imie := 'Bozydar';
    END IF;
    IF LENGTH(NEW.nazwisko) = 0 THEN
        RAISE WARNING 'Nie podano nazwiska nowego studenta. Z tego wzgledu nadano mu nazwisko Kolec.';
        NEW.nazwisko := 'Kolec';
    END IF;
    IF EXISTS(SELECT * FROM prj.student WHERE email = NEW.email) THEN
        RAISE EXCEPTION 'Istnieje juz student z identycznym adresem email.';
    END IF;
    IF NEW.data_urodzenia < '01-01-1900'::DATE THEN
        RAISE WARNING 'Podana data niepoprawna. Jej wartosc zmieniono na 01-01-1900';
        NEW.data_urodzenia := '01-01-1900'::DATE;
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowegoStudentaTrigger
BEFORE INSERT OR UPDATE ON prj.student
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowegoStudenta();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNoweStudent_Informacje()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT * FROM prj.student WHERE NEW.nr_albumu = nr_albumu) THEN
        RAISE EXCEPTION 'Nie istnieje student o numerze albumu %.', NEW.nr_albumu;
    END IF;
    IF LENGTH(NEW.miejsce_zamieszkania) = 0 THEN
        RAISE WARNING 'Nie podano informacji o miejscu zamieszkania. Z tego wzgledu miejscowosc ustawiono na Zlotoryja.';
        NEW.miejsce_zamieszkania := 'Zlotoryja';
    END IF;
    IF LENGTH(NEW.plec) = 0 THEN
        RAISE WARNING 'Nie podano informacji o plci studenta. Z tego wzgledu ustawiono "Nie podano".';
        NEW.plec := 'Nie podano';
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNoweStudent_InformacjeTrigger
BEFORE INSERT OR UPDATE ON prj.student_informacje
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNoweStudent_Informacje();

----------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION prj.walidujNowyStudent_Kierunek()
RETURNS TRIGGER AS
$$
BEGIN
    IF NOT EXISTS(SELECT * FROM prj.student WHERE NEW.nr_albumu = nr_albumu) THEN
        RAISE EXCEPTION 'Nie istnieje student o numerze albumu %.', NEW.nr_albumu;
    END IF;
    IF NOT EXISTS(SELECT *
        FROM prj.kierunek
        WHERE NEW.id_kierunek = id_kierunek
        OR NEW.skrot_nazwy = skrot_nazwy)
    THEN
        RAISE EXCEPTION 'Nie istnieje kierunek o ID = % i skrocie %.', NEW.id_kierunek, NEW.skrot_nazwy;
    END IF;
    IF NEW.data_rozpoczecia < '01-01-1900'::DATE THEN
        RAISE WARNING 'Podana data rozpoczecia jest niepoprawna. Jej wartosc zmieniono na 01-01-1900';
        NEW.data_rozpoczecia := '01-01-1900'::DATE;
    END IF;
    IF NEW.data_zakonczenia < NEW.data_rozpoczecia THEN
        RAISE WARNING 'Data zakonczenia nie moze byc starsza niz data rozpoczecia. Jej wartosc zmieniono na date rozpoczecia + dlugosc trwania kierunkow.';
        NEW.data_zakonczenia := (NEW.data_rozpoczecia + CONCAT(((SELECT dlugosc FROM prj.kierunek WHERE NEW.id_kierunek = id_kierunek)/2)::TEXT, ' year')::INTERVAL);
    END IF;
    RETURN NEW;
END
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER prj_walidujNowyStudent_KierunekTrigger
BEFORE INSERT OR UPDATE ON prj.student_kierunek
FOR EACH ROW EXECUTE PROCEDURE prj.walidujNowyStudent_Kierunek();
