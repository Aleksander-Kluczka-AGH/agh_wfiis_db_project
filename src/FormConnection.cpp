#include "../include/Forms.hpp"

void formConnection()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "POLACZENIE Z BAZA DANYCH");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;

    ImGui::InputTextWithHint("##bcon_host", "Host", DATA::buf_host, DATA::buf_host.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(128)");

    ImGui::InputTextWithHint("##bcon_port", "Port", DATA::buf_port, DATA::buf_port.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("varchar(8)");

    ImGui::InputTextWithHint("##bcon_dbname", "Nazwa bazy danych", DATA::buf_dbname, DATA::buf_dbname.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bcon_user", "Nazwa uzytkownika", DATA::buf_user, DATA::buf_user.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bcon_password", "Haslo", DATA::buf_password, DATA::buf_password.size(), ImGuiInputTextFlags_Password);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    if(ImGui::Button("Sprawdz polaczenie"))
    {
        // DATA::clicked = true;
        // try
        // {
        //     // char buffer[1024];
        //     // std::sprintf(buffer, "host=%s dbname=%s user=%s password=%s sslmode=allow",
        //     //     DATA::buf_host.getBuffer(),
        //     //     DATA::buf_dbname.getBuffer(),
        //     //     DATA::buf_user.getBuffer(),
        //     //     DATA::buf_password.getBuffer());
        //     pqxx::connection C(str.str().c_str());
        //     if(C.is_open())
        //     {
        //         DATA::is_conn = true;
        //     }
        //     else
        //     {
        //         DATA::is_conn = false;
        //     }
        // }
        // catch (const std::exception& e)
        // {
        //     DATA::exception_message = e.what();
        // }
        tryConnect(str.str().c_str());
        DATA::requested_results = true;
    }

    ImGui::SameLine();
    if(DATA::is_conn)
    {
        // ImGui::PushStyleColor(ImGuiCol_Text, sf::Color::Green);
        ImGui::TextColored(sf::Color::Green, "CONNECTION SUCCESSFULL");
        // ImGui::PopStyleColor();
    }
    else if(DATA::requested_results)
    {
        // ImGui::PushStyleColor(ImGuiCol_Text, sf::Color::Red);
        ImGui::TextColored(sf::Color::Red, "CONNECTION FAILED: %s", DATA::exception_message.c_str());
        // ImGui::PopStyleColor();
    }
}
