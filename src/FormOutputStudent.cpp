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
    tableFromQuery("SELECT * FROM prj.OutStudent;",
        {1, 2, 4, 5, 6, 7, 8, 9, 12, 10, 11});
}

// view: prj.OutStudent
