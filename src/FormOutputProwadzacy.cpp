#include "../include/Forms.hpp"

void formOutputProwadzacy()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA PROWADZACYCH");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT pr.id_prowadzacy, pr.imie, pr.drugie_imie, pr.nazwisko, pr.email, wy.nazwa AS wydzial, wy.skrot_nazwy AS skrot FROM prj.prowadzacy PR FULL JOIN prj.wydzial_prowadzacy USING(id_prowadzacy) FULL JOIN prj.wydzial WY USING (id_wydzial) ORDER BY 1;",
        {1, 2, 4, 5, 6, 7});
}
