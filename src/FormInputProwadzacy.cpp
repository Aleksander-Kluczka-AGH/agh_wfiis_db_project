#include "../include/Forms.hpp"

void formInputProwadzacy()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY PROWADZACY");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_prow_id", "ID", DATA::buf_id, DATA::buf_id.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_prow_imie", "Imie", DATA::buf_imie, DATA::buf_imie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_prow_drugieimie", "Drugie imie", DATA::buf_drugieimie, DATA::buf_drugieimie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_prow_nazwisko", "Nazwisko", DATA::buf_nazwisko, DATA::buf_nazwisko.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");
    
    ImGui::InputTextWithHint("##bin_prow_email", "Email", DATA::buf_email, DATA::buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;
    
    std::stringstream ss;
    ss << "INSERT INTO prj.prowadzacy (id_prowadzacy, imie, drugie_imie, nazwisko, email) values ("
        << DATA::buf_id.toInt() << ", "
        << std::quoted(DATA::buf_imie.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_drugieimie.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_nazwisko.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_email.getBuffer(), '\'') << ");";

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    tryConnect(str.str().c_str());
    chooseFromQuery("SELECT id_przedmiot, nazwa, semestr FROM prj.przedmiot EXCEPT SELECT id_przedmiot, nazwa, semestr FROM prj.prowadzacy_przedmiot JOIN prj.przedmiot USING (id_przedmiot) ORDER BY 1;", "Wybierz przedmiot:", 1);
    
    if(DATA::current_choice > 0)
    {
        // need to find ID of an item in a databse, not its position in the result table
        auto ID = (DATA::qresult[DATA::current_choice-1]["id_przedmiot"]).as<int>();
        ss << "INSERT INTO prj.prowadzacy_przedmiot (id_przedmiot, id_prowadzacy) values ("
            << ID << ", "
            << DATA::buf_id.toInt() << ");";
    }

    auto filled = (DATA::buf_id != 0)
        && (DATA::buf_imie.length() != 0)
        && (DATA::buf_drugieimie.length() != 0)
        && (DATA::buf_nazwisko.length() != 0)
        && (DATA::buf_email.length() != 0);

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }
    if(DATA::query_failed)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}
