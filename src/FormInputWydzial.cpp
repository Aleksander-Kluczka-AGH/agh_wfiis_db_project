#include "../include/Forms.hpp"

void formInputWydzial()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY WYDZIAL");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_kier_nazwa", "Nazwa", DATA::buf_nazwa, DATA::buf_nazwa.size());
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_kier_skrot", "Skrot nazwy", DATA::buf_skrotnazwy, DATA::buf_skrotnazwy.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(8)");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;
    
    std::stringstream ss;
    ss << "INSERT INTO prj.wydzial (skrot_nazwy, nazwa) values ("
        << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_nazwa.getBuffer(), '\'') << ");";

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto filled = (DATA::buf_nazwa.length() != 0
        && DATA::buf_skrotnazwy.length() != 0);

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }
    if(DATA::query_failed)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}
