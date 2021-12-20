#include "../include/Forms.hpp"
#include "../include/Util.hpp"

void formInputPrzedmiot()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY PRZEDMIOT");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_prze_id", "ID", DATA::buf_id, DATA::buf_id.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_prze_nazwa", "Nazwa", DATA::buf_nazwa, DATA::buf_nazwa.size());
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_prze_semestr", "Numer semestru", DATA::buf_semestr, DATA::buf_semestr.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_prze_ects", "Liczba punktow ECTS", DATA::buf_ects, DATA::buf_ects.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_prze_miejsca", "Liczba miejsc", DATA::buf_miejsca, DATA::buf_miejsca.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::Checkbox("Egzamin", &DATA::buf_egzamin);

    ImGui::InputTextWithHint("##bin_prze_typ", "Typ przedmiotu (obowiazkowy/obieralny)", DATA::buf_typ, DATA::buf_typ.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(16)");

    ImGui::InputTextMultilineWithHint("##bin_prze_opis", "Opis", DATA::buf_opis, DATA::buf_opis.size(), sf::Vector2f(0.f, 300.f));
    ImGui::SameLine(); ImGui::Text("varchar(1024)");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    std::stringstream ss;
    ss << "INSERT INTO prj.przedmiot (id_przedmiot, nazwa, semestr, liczba_ects, miejsca, egzamin) values ("
        << DATA::buf_id.toInt() << ", "
        << std::quoted(DATA::buf_nazwa.getBuffer(), '\'') << ", "
        << DATA::buf_semestr.toInt() << ", "
        << DATA::buf_ects.toInt() << ", "
        << DATA::buf_miejsca.toInt() << ", "
        << (DATA::buf_egzamin ? "true" : "false") << ");";
    
    if((DATA::buf_typ != 0) && (DATA::buf_opis != 0))
    {
        ss << "INSERT INTO prj.przedmiot_informacje (id_przedmiot, typ, opis) values ("
            << DATA::buf_id.toInt() << ", "
            << std::quoted(DATA::buf_typ.getBuffer(), '\'') << ", "
            << std::quoted(DATA::buf_opis.getBuffer(), '\'') << ");"; 
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    tryConnect(str.str().c_str());
    chooseFromQuery("SELECT id_kierunek, nazwa, stopien FROM prj.kierunek ORDER BY 1;", "Wybierz kierunek:", 1);
    
    if(DATA::current_choice > 0)
    {
        auto ID = (DATA::qresult[DATA::current_choice-1]["id_kierunek"]).as<int>();
        ss << "INSERT INTO prj.przedmiot_kierunek (id_kierunek, skrot_nazwy, id_przedmiot) values ("
            << ID << ", "
            << "(SELECT skrot_nazwy FROM prj.kierunek WHERE id_kierunek = " << ID << "), "
            << DATA::buf_id.toInt() << ");";
    }

    // current system does not support multiple choices from queries
    // suggestion: change qresults to std::vector<pqxx::result>
    // same for the flags (or maybe create a struct!) (and make vector of structs)

    // DATA::current_choice = 0;
    // DATA::requested_results = false;
    // tryConnect(str.str().c_str());
    // chooseFromQuery("SELECT id_prowadzacy, imie, nazwisko, email FROM prj.prowadzacy EXCEPT SELECT id_prowadzacy, imie, nazwisko, email FROM prj.prowadzacy_przedmiot JOIN prj.prowadzacy USING (id_prowadzacy) ORDER BY 1;",
    //     "Dostepni prowadzacy:", 2, "##submit2");
    
    // if(DATA::current_choice > 0)
    // {
    //     auto ID = (DATA::qresult[DATA::current_choice-1]["id_prowadzacy"]).as<int>();
    //     ss << "INSERT INTO prj.prowadzacy_przedmiot (id_przedmiot, id_prowadzacy) values("
    //         << DATA::buf_id.toInt() << ", "
    //         << ID << ");";
    // }

    auto filled = (DATA::buf_id != 0)
        && (DATA::buf_nazwa.length() != 0)
        && (DATA::buf_semestr.length() != 0)
        && (DATA::buf_ects.length() != 0)
        && (DATA::buf_miejsca.length() != 0);

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }
    if(DATA::query_failed)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}
