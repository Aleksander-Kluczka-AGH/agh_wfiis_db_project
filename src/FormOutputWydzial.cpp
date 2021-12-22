#include "../include/Forms.hpp"

void formOutputWydzial()
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
    tableFromQuery("SELECT id_wydzial, nazwa, wy.skrot_nazwy, COUNT(id_prowadzacy) AS prowadzacy, COUNT(id_kierunek) AS kierunki FROM prj.wydzial WY FULL JOIN prj.wydzial_prowadzacy USING (id_wydzial) FULL JOIN prj.wydzial_kierunek USING (id_wydzial) GROUP BY 1, 2, 3 ORDER BY 1;",
        {1, 2, 3, 4, 5});
}

// SELECT id_wydzial, nazwa, wy.skrot_nazwy, COUNT(id_prowadzacy) AS prowadzacy, COUNT(id_kierunek) AS kierunki
// FROM prj.wydzial WY
// FULL JOIN prj.wydzial_prowadzacy USING (id_wydzial)
// FULL JOIN prj.wydzial_kierunek USING (id_wydzial)
// GROUP BY 1, 2, 3
// ORDER BY 1;
