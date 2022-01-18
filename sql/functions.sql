
CREATE OR REPLACE FUNCTION prj.CzyKierunekNaWydziale(nazwa_kierunku VARCHAR(64), id_w INTEGER)
RETURNS BOOLEAN AS
$$
BEGIN
	RETURN (SELECT EXISTS
		(SELECT *
		FROM prj.wydzial_kierunek
		JOIN prj.kierunek KI USING (id_kierunek)
		WHERE nazwa_kierunku = ki.nazwa
		AND id_w = id_wydzial));
END
$$
LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION prj.WydzialBezKierunku (nazwa_k VARCHAR(64))
RETURNS TABLE (id_wydzial INTEGER, nazwa VARCHAR, skrot_nazwy VARCHAR) AS
$$
BEGIN
	RETURN QUERY
	    SELECT wy.id_wydzial, wy.nazwa, wy.skrot_nazwy
	    FROM prj.wydzial WY
	    WHERE (SELECT * FROM prj.CzyKierunekNaWydziale(nazwa_k, wy.id_wydzial)) = False
	    ORDER BY 1;
END
$$
LANGUAGE 'plpgsql';
