#include "../include/Forms.hpp"

void formOutputPrzedmiot()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA PRZEDMIOTOW");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT id_przedmiot AS ID, pr.nazwa, semestr, liczba_ects AS ECTS, miejsca, egzamin, typ, opis, ki.nazwa AS kierunek FROM prj.przedmiot PR FULL JOIN prj.przedmiot_informacje USING (id_przedmiot) FULL JOIN prj.przedmiot_kierunek USING (id_przedmiot) JOIN prj.kierunek KI USING (id_kierunek) ORDER BY 1;",
        {1, 2, 7, 9, 3, 4, 6, 5, 8});
}
