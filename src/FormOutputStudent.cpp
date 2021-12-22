#include "../include/Forms.hpp"

void formOutputStudent()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA STUDENTOW");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT nr_albumu, imie, drugie_imie, nazwisko, email, data_urodzenia, miejsce_zamieszkania, plec, data_rozpoczecia, ki.skrot_nazwy AS kierunek, ki.stopien, wy.skrot_nazwy AS wydzial FROM prj.student FULL JOIN prj.student_informacje USING (nr_albumu) LEFT JOIN prj.student_kierunek USING (nr_albumu) LEFT JOIN prj.kierunek KI USING (id_kierunek) FULL JOIN prj.wydzial_kierunek USING (id_kierunek) FULL JOIN prj.wydzial WY USING (id_wydzial) ORDER BY 1;",
        {1, 2, 4, 5, 6, 7, 8, 9, 12, 10, 11});
}

// SELECT nr_albumu,
//     imie,
//     drugie_imie,
//     nazwisko,
//     email,
//     data_urodzenia,
//     miejsce_zamieszkania,
//     plec,
//     data_rozpoczecia,
//     ki.skrot_nazwy AS kierunek,
//     ki.stopien,
//     wy.skrot_nazwy AS wydzial
// FROM prj.student
// FULL JOIN prj.student_informacje USING (nr_albumu)
// LEFT JOIN prj.student_kierunek USING (nr_albumu)
// LEFT JOIN prj.kierunek KI USING (id_kierunek)
// FULL JOIN prj.wydzial_kierunek USING (id_kierunek)
// FULL JOIN prj.wydzial WY USING (id_wydzial) ORDER BY 1;
