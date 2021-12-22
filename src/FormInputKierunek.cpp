#include "../include/Forms.hpp"

void formInputKierunek()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY KIERUNEK");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_kier_nazwa", "Nazwa", DATA::buf_nazwa, DATA::buf_nazwa.size());
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_kier_skrot", "Skrot nazwy", DATA::buf_skrotnazwy, DATA::buf_skrotnazwy.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(8)");

    ImGui::InputTextWithHint("##bin_kier_miejsca", "Liczba miejsc", DATA::buf_miejsca, DATA::buf_miejsca.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_kier_dlugosc", "Dlugosc toku studiow (w semestrach)", DATA::buf_semestr, DATA::buf_semestr.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_kier_stopien", "Stopien", DATA::buf_stopien, DATA::buf_stopien.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_kier_prog", "Prog punktowy", DATA::buf_prog, DATA::buf_prog.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;
    
    std::stringstream ss;
    ss << "INSERT INTO prj.kierunek (skrot_nazwy, nazwa, liczba_miejsc, dlugosc, stopien) values ("
        << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_nazwa.getBuffer(), '\'') << ", "
        << DATA::buf_miejsca.toInt() << ", "
        << DATA::buf_semestr.toInt() << ", "
        << DATA::buf_stopien.toInt() << ");";
    
    if(DATA::buf_prog.length() != 0)
    {
        ss << "INSERT INTO prj.kierunek_wymagania (skrot_nazwy, id_kierunek, prog_punktowy) values ("
            << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << ", "
            << "(SELECT id_kierunek FROM prj.kierunek WHERE skrot_nazwy = "
                << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << "), "
            << DATA::buf_prog.toInt() << ");";
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // find a faculty where the field with such id does not yet exist
    std::stringstream query;
    query << "SELECT wy.id_wydzial, wy.nazwa, wy.skrot_nazwy "
        << "FROM prj.wydzial WY"
        // << "FULL JOIN prj.wydzial_kierunek WK USING (id_wydzial)"
        // << "WHERE wk.skrot_nazwy != " << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'')
        << ";";

    tryConnect(str.str().c_str());
    chooseFromQuery(query.str(), "Przypisz do wydzialu:", 2);
    
    if(DATA::current_choice > 0)
    {
        // need to find ID of an item in a databse, not its position in the result table
        auto ID = (DATA::qresult[DATA::current_choice-1]["id_wydzial"]).as<int>();
        ss << "INSERT INTO prj.wydzial_kierunek (id_wydzial, id_kierunek, skrot_nazwy) values ("
            << ID << ", "
            << "(SELECT id_kierunek FROM prj.kierunek WHERE skrot_nazwy = "
                << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << "), "
            << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << ");";
    }

    auto filled = (DATA::buf_nazwa.length() != 0
        && DATA::buf_skrotnazwy.length() != 0
        && DATA::buf_miejsca.length() != 0
        && DATA::buf_semestr.length() != 0
        && DATA::buf_stopien.length() != 0);

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }
    if(DATA::query_failed)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}
