
CREATE SCHEMA prj;

CREATE SEQUENCE prj.wydzial_id_wydzial_seq;

CREATE TABLE prj.wydzial (
                id_wydzial INTEGER NOT NULL DEFAULT nextval('prj.wydzial_id_wydzial_seq'),
                nazwa VARCHAR(64) NOT NULL,
                skrot_nazwy VARCHAR(8) NOT NULL,
                CONSTRAINT wydzial_pk PRIMARY KEY (id_wydzial)
);

ALTER SEQUENCE prj.wydzial_id_wydzial_seq OWNED BY prj.wydzial.id_wydzial;

CREATE SEQUENCE prj.prowadzacy_id_prowadzacy_seq;

CREATE TABLE prj.prowadzacy (
                id_prowadzacy INTEGER NOT NULL DEFAULT nextval('prj.prowadzacy_id_prowadzacy_seq'),
                imie VARCHAR(32) NOT NULL,
                drugie_imie VARCHAR(32),
                nazwisko VARCHAR(32) NOT NULL,
                email VARCHAR(64) NOT NULL,
                CONSTRAINT prowadzacy_pk PRIMARY KEY (id_prowadzacy)
);

ALTER SEQUENCE prj.prowadzacy_id_prowadzacy_seq OWNED BY prj.prowadzacy.id_prowadzacy;

CREATE TABLE prj.wydzial_prowadzacy (
                id_prowadzacy INTEGER NOT NULL,
                id_wydzial INTEGER NOT NULL,
                CONSTRAINT wydzial_prowadzacy_pk PRIMARY KEY (id_prowadzacy, id_wydzial)
);

CREATE SEQUENCE prj.przedmiot_id_przedmiot_seq;

CREATE TABLE prj.przedmiot (
                id_przedmiot INTEGER NOT NULL DEFAULT nextval('prj.przedmiot_id_przedmiot_seq'),
                nazwa VARCHAR(64) NOT NULL,
                semestr INTEGER NOT NULL,
                liczba_ects INTEGER NOT NULL,
                miejsca INTEGER NOT NULL,
                typ VARCHAR(16) NOT NULL,
                opis VARCHAR(1024),
                egzamin BOOLEAN NOT NULL,
                CONSTRAINT przedmiot_pk PRIMARY KEY (id_przedmiot)
);

ALTER SEQUENCE prj.przedmiot_id_przedmiot_seq OWNED BY prj.przedmiot.id_przedmiot;

CREATE TABLE prj.prowadzacy_przedmiot (
                id_przedmiot INTEGER NOT NULL,
                id_prowadzacy INTEGER NOT NULL,
                CONSTRAINT prowadzacy_przedmiot_pk PRIMARY KEY (id_przedmiot, id_prowadzacy)
);

CREATE SEQUENCE prj.kierunek_id_kierunek_seq;

CREATE TABLE prj.kierunek (
                skrot_nazwy VARCHAR(8) NOT NULL,
                id_kierunek INTEGER NOT NULL DEFAULT nextval('prj.kierunek_id_kierunek_seq'),
                nazwa VARCHAR(64) NOT NULL,
                liczba_miejsc INTEGER NOT NULL,
                dlugosc INTEGER NOT NULL,
                stopien INTEGER NOT NULL,
                CONSTRAINT kierunek_pk PRIMARY KEY (skrot_nazwy, id_kierunek)
);

ALTER SEQUENCE prj.kierunek_id_kierunek_seq OWNED BY prj.kierunek.id_kierunek;

CREATE TABLE prj.wydzial_kierunek (
                id_wydzial INTEGER NOT NULL,
                skrot_nazwy VARCHAR(8) NOT NULL,
                id_kierunek INTEGER NOT NULL,
                CONSTRAINT wydzial_kierunek_pk PRIMARY KEY (id_wydzial, skrot_nazwy, id_kierunek)
);

CREATE SEQUENCE prj.kierunek_id_kierunek_seq_2;

CREATE TABLE prj.kierunek_wymagania (
                skrot_nazwy VARCHAR(8) NOT NULL,
                id_kierunek INTEGER NOT NULL DEFAULT nextval('prj.kierunek_id_kierunek_seq_2'),
                prog_punktowy INTEGER NOT NULL,
                CONSTRAINT kierunek_wymagania_pk PRIMARY KEY (skrot_nazwy, id_kierunek)
);

ALTER SEQUENCE prj.kierunek_id_kierunek_seq_2 OWNED BY prj.kierunek_wymagania.id_kierunek;

CREATE TABLE prj.przedmiot_kierunek (
                id_przedmiot INTEGER NOT NULL,
                skrot_nazwy VARCHAR(8) NOT NULL,
                id_kierunek INTEGER NOT NULL,
                CONSTRAINT przedmiot_kierunek_pk PRIMARY KEY (id_przedmiot, skrot_nazwy, id_kierunek)
);

CREATE SEQUENCE prj.student_nr_albumu_seq;

CREATE TABLE prj.student (
                nr_albumu INTEGER NOT NULL DEFAULT nextval('prj.student_nr_albumu_seq'),
                imie VARCHAR(32) NOT NULL,
                drugie_imie VARCHAR(32),
                nazwisko VARCHAR(32) NOT NULL,
                email VARCHAR(64) NOT NULL,
                data_urodzenia DATE NOT NULL,
                CONSTRAINT student_pk PRIMARY KEY (nr_albumu)
);

ALTER SEQUENCE prj.student_nr_albumu_seq OWNED BY prj.student.nr_albumu;

CREATE TABLE prj.student_informacje (
                nr_albumu INTEGER NOT NULL,
                miejsce_zamieszkania VARCHAR(64) NOT NULL,
                plec VARCHAR(32) NOT NULL,
                imie_ojca VARCHAR(32),
                imie_matki VARCHAR(32),
                CONSTRAINT student_informacje_pk PRIMARY KEY (nr_albumu)
);

CREATE TABLE prj.student_przedmiot (
                id_przedmiot INTEGER NOT NULL,
                nr_albumu INTEGER NOT NULL,
                CONSTRAINT student_przedmiot_pk PRIMARY KEY (id_przedmiot, nr_albumu)
);

CREATE TABLE prj.student_ocena (
                id_przedmiot INTEGER NOT NULL,
                nr_albumu INTEGER NOT NULL,
                ocena DOUBLE PRECISION,
                CONSTRAINT student_ocena_pk PRIMARY KEY (id_przedmiot, nr_albumu)
);

CREATE TABLE prj.student_kierunek (
                nr_albumu INTEGER NOT NULL,
                skrot_nazwy VARCHAR(8) NOT NULL,
                id_kierunek INTEGER NOT NULL,
                data_rozpoczecia DATE NOT NULL,
                data_zakonczenia DATE NOT NULL,
                CONSTRAINT student_kierunek_pk PRIMARY KEY (nr_albumu, skrot_nazwy, id_kierunek)
);

ALTER TABLE prj.wydzial_prowadzacy ADD CONSTRAINT wydzial_wydzial_prowadzacy_fk
FOREIGN KEY (id_wydzial)
REFERENCES prj.wydzial (id_wydzial)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.wydzial_kierunek ADD CONSTRAINT wydzial_wydzial_kierunek_fk
FOREIGN KEY (id_wydzial)
REFERENCES prj.wydzial (id_wydzial)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.prowadzacy_przedmiot ADD CONSTRAINT prowadzacy_prowadzacy_przedmiot_fk
FOREIGN KEY (id_prowadzacy)
REFERENCES prj.prowadzacy (id_prowadzacy)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.wydzial_prowadzacy ADD CONSTRAINT prowadzacy_wydzial_prowadzacy_fk
FOREIGN KEY (id_prowadzacy)
REFERENCES prj.prowadzacy (id_prowadzacy)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.przedmiot_kierunek ADD CONSTRAINT przedmiot_przedmiot_kierunek_fk
FOREIGN KEY (id_przedmiot)
REFERENCES prj.przedmiot (id_przedmiot)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.student_przedmiot ADD CONSTRAINT przedmiot_student_przedmiot_fk
FOREIGN KEY (id_przedmiot)
REFERENCES prj.przedmiot (id_przedmiot)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.prowadzacy_przedmiot ADD CONSTRAINT przedmiot_prowadzacy_przedmiot_fk
FOREIGN KEY (id_przedmiot)
REFERENCES prj.przedmiot (id_przedmiot)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.student_kierunek ADD CONSTRAINT kierunek_student_kierunek_fk
FOREIGN KEY (skrot_nazwy, id_kierunek)
REFERENCES prj.kierunek (skrot_nazwy, id_kierunek)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.przedmiot_kierunek ADD CONSTRAINT kierunek_przedmiot_kierunek_fk
FOREIGN KEY (skrot_nazwy, id_kierunek)
REFERENCES prj.kierunek (skrot_nazwy, id_kierunek)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.kierunek_wymagania ADD CONSTRAINT kierunek_kierunek_wymagania_fk
FOREIGN KEY (skrot_nazwy, id_kierunek)
REFERENCES prj.kierunek (skrot_nazwy, id_kierunek)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.wydzial_kierunek ADD CONSTRAINT kierunek_wydzial_kierunek_fk
FOREIGN KEY (skrot_nazwy, id_kierunek)
REFERENCES prj.kierunek (skrot_nazwy, id_kierunek)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.student_kierunek ADD CONSTRAINT student_student_kierunek_fk
FOREIGN KEY (nr_albumu)
REFERENCES prj.student (nr_albumu)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.student_przedmiot ADD CONSTRAINT student_student_przedmiot_fk
FOREIGN KEY (nr_albumu)
REFERENCES prj.student (nr_albumu)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.student_informacje ADD CONSTRAINT student_student_informacje_fk
FOREIGN KEY (nr_albumu)
REFERENCES prj.student (nr_albumu)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE prj.student_ocena ADD CONSTRAINT student_przedmiot_student_ocena_fk
FOREIGN KEY (id_przedmiot, nr_albumu)
REFERENCES prj.student_przedmiot (id_przedmiot, nr_albumu)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;
