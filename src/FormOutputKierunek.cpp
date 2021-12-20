#include "../include/Forms.hpp"

void formOutputKierunek()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA KIERUNKOW");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT id_kierunek, nazwa, liczba_miejsc, dlugosc, stopien FROM prj.kierunek ORDER BY 1", {1, 2, 3, 4, 5});
}
