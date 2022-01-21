INSERT INTO prj.wydzial(nazwa, skrot_nazwy) values
    ('Wydzial Fizyki i Informatyki Stosowanej',             'WFiIS'),
    ('Wydzial Zarzadzania',                                 'WZ'),
    ('Wydzial Matematyki Stosowanej',                       'WMS'),
    ('Wydzial Odlewnictwa',                                 'WO'),
    ('Wydzial Informatyki, Elektroniki i Telekomunikacji',  'WIEiT');

INSERT INTO prj.kierunek(skrot_nazwy, nazwa, liczba_miejsc, dlugosc, stopien) values
    ('IS',  'Informatyka Stosowana',                120,    7,  1),
    ('FT',  'Fizyka Techniczna',                    120,    7,  1),
    ('Z',   'Zarzadzanie',                          80,     7,  1),
    ('IE',  'Informatyka i Ekonometria',            80,     7,  1),
    ('M',   'Matematyka',                           210,    7,  1),
    ('IPO', 'Inzynieria Procesow Odlewczych',       75,     7,  1),
    ('TTM', 'Tworzywa i Technologie Motoryzacyjne', 75,     7,  1),
    ('TI',  'Teleinformatyka',                      250,    7,  1),
    ('CB',  'Cyberbezpieczenstwo',                  250,    7,  1);

INSERT INTO prj.kierunek_wymagania(skrot_nazwy, id_kierunek, prog_punktowy) values
    ('IS',  1,  980),
    ('FT',  2,  930),
    ('Z',   3,  900),
    ('IE',  4,  790),
    ('M',   5,  890),
    ('IPO', 6,  710),
    ('TTM', 7,  710),
    ('TI',  8,  975),
    ('CB',  9,  950);

INSERT INTO prj.wydzial_kierunek(id_wydzial, skrot_nazwy, id_kierunek) values
    (1, 'IS',  1),
    (1, 'FT',  2),
    (2, 'Z',   3),
    (2, 'IE',  4),
    (3, 'M',   5),
    (4, 'IPO', 6),
    (4, 'TTM', 7),
    (5, 'TI',  8),
    (5, 'CB',  9);

INSERT INTO prj.prowadzacy(imie, drugie_imie, nazwisko, email) values
    ('Jan',         'Piotr',        'Makrela',          'jpmakrela@onet.pl'),
    ('Joanna',      'Marta',        'Drwal',            'jmdrwal@uni.edu.pl'),
    ('Aleksander',  'Stanislaw',    'Czarny',           'asc@o2.pl'),
    ('Antoni',      'Gustaw',       'Humbak',           'aghumbak@uni.edu.pl'),
    ('Hubert',      'Stanislaw',    'Krtan',            'hsk@uj.edu.pl'),
    ('Hanna',       'Weronika',     'Dynia-Przetarg',   'hwdp@gmail.com'),
    ('Tomasz',      'Ignacy',       'Przetarg',         'tiprzetarg@uni.edu.pl'),
    ('Barbara',     'Martyna',      'Las',              'bmlas@uni.edu.pl'),
    ('Joanna',      'Kalina',       'Jasinska',         'jjasinska@uni.edu.pl'),
    ('Adam',        'Kacper',       'Kwarcowski',       'kwarcowski@onet.pl'),
    ('Gustaw',      'Ginter',       'Grusza',           'ggg@uni.edu.pl');

INSERT INTO prj.wydzial_prowadzacy(id_prowadzacy, id_wydzial) values
    (1,     1),
    (2,     1),
    (3,     2),
    (4,     2),
    (5,     3),
    (6,     3),
    (7,     4),
    (8,     4),
    (9,     5),
    (10,    5),
    (11,    5);

INSERT INTO prj.przedmiot(nazwa, semestr, liczba_ects, miejsca, typ, opis, egzamin) values
    ('Matematyka 1',                        1, 6, 250,  'obowiazkowy',  'Podstawy analizy matematycznej.',                                      true),
    ('Matematyka 2',                        2, 7, 250,  'obowiazkowy',  'Analiza matematyczna.',                                                true),
    ('Podstawy Informatyki',                1, 4, 250,  'obowiazkowy',  'Wprowadzenie do jezykow programowania.',                               false),
    ('Podstawy Zarzadzania',                1, 4, 80,   'obowiazkowy',  'Podstawy zarzadzania.',                                                false),
    ('Algebra Liniowa',                     2, 6, 210,  'obowiazkowy',  'Wstep do algebry liniowej.',                                           true),
    ('Statystyka',                          3, 3, 210,  'obowiazkowy',  'Wybrane zagadnienia ze statystyki.',                                   false),
    ('Algorytmika',                         3, 5, 120,  'obowiazkowy',  'Wybrane zagadnienia z algorytmiki.',                                   true),
    ('Zaawansowane Techniki Internetowe',   4, 6, 40,   'obieralny',    'Wspolczesne zaawansowane techniki stosowane w sieci Internet.',        false),
    ('Alchemia',                            4, 8, 20,   'obieralny',    'Tajemnice warzenia mikstur oraz przepisywania zwojow alchemicznych.',  true);

INSERT INTO prj.przedmiot_kierunek(id_przedmiot, skrot_nazwy, id_kierunek) values
    (1, 'IS',   1),
    (2, 'IS',   1),
    (3, 'IS',   1),
    (7, 'IS',   1),
    (1, 'FT',   2),
    (5, 'FT',   2),
    (6, 'FT',   2),
    (7, 'FT',   2),
    (1, 'Z',    3),
    (2, 'Z',    3),
    (4, 'Z',    3),
    (1, 'IE',   4),
    (2, 'IE',   4),
    (3, 'IE',   4),
    (6, 'IE',   4),
    (1, 'M',    5),
    (2, 'M',    5),
    (5, 'M',    5),
    (6, 'M',    5),
    (1, 'IPO',  6),
    (6, 'IPO',  6),
    (7, 'IPO',  6),
    (1, 'TTM',  7),
    (6, 'TTM',  7),
    (7, 'TTM',  7),
    (1, 'TI',   8),
    (2, 'TI',   8),
    (3, 'TI',   8),
    (8, 'TI',   8),
    (1, 'CB',   9),
    (2, 'CB',   9),
    (3, 'CB',   9),
    (7, 'CB',   9);

INSERT INTO prj.prowadzacy_przedmiot(id_przedmiot, id_prowadzacy) values
    (1, 1),
    (2, 1),
    (3, 2),
    (4, 3),
    (5, 4),
    (6, 5),
    (7, 6),
    (8, 7),
    (9, 8);

INSERT INTO prj.student(nr_albumu, imie, drugie_imie, nazwisko, email, data_urodzenia) values
    (1, 'Jan',      '',             'Todowski',     'jantodowski@student.uni.edu.pl',   '01-01-2000'),
    (2, 'Kacper',   'Tomasz',       'Kowalski',     'kkowalski@student.uni.edu.pl',     '25-05-2000'),
    (3, 'Piotr',    'Piotr',        'Piotrowski',   'ppp@student.uni.edu.pl',           '30-05-2000'),
    (4, 'Anna',     'Maria',        'Smutna',       'asmutna@student.uni.edu.pl',       '28-02-1999'),
    (5, 'Justyna',  'Magdalena',    'Tkaczyk',      'jkaczyk@student.uni.edu.pl',       '11-09-1999');

INSERT INTO prj.student_informacje(nr_albumu, miejsce_zamieszkania, plec, imie_ojca, imie_matki) values
    (1, 'Warszawa',     'Mezczyzna',    null,           null),
    (2, 'Gdansk',       'Mezczyzna',    'Marian',       'Elzbieta'),
    (3, 'Zlotoryja',    'Nie podano',   'Tadeusz',      'Maria'),
    (4, 'Rybnik',       'Kobieta',      'Tomasz',       'Krystyna'),
    (5, 'Olsztyn',      'Kobieta',      'Wladyslaw',    'Zofia');

INSERT INTO prj.student_kierunek(nr_albumu, skrot_nazwy, id_kierunek, data_rozpoczecia, data_zakonczenia) values
    (1, 'IS', 1, '19-01-2020', '01-01-1025'),
    (2, 'TI', 8, '02-10-2019', '01-01-1025'),
    (3, 'Z', 3, '02-10-2019', '01-01-1025'),
    (4, 'CB', 9, '31-01-2019', '01-01-1025'),
    (5, 'IPO', 6, '4-10-2018', '01-01-1025');
