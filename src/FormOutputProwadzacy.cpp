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
    tableFromQuery("SELECT * FROM prj.OutProwadzacy;",
        {1, 2, 4, 5, 6, 7});
}

// view: prj.OutProwadzacy
