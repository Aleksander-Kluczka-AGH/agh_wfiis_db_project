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
    tableFromQuery("SELECT * FROM prj.OutPrzedmiot;",
        {1, 2, 7, 9, 3, 4, 6, 5, 8});
}

// view: prj.OutPrzedmiot
