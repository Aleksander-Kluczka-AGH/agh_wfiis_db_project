#include "../include/Forms.hpp"

void formInputStudent()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY STUDENT");
    ImGui::NewLine();    

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_stud_id", "Numer albumu", DATA::buf_id, DATA::buf_id.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_stud_imie", "Imie", DATA::buf_imie, DATA::buf_imie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_drugieimie", "Drugie imie", DATA::buf_drugieimie, DATA::buf_drugieimie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_nazwisko", "Nazwisko", DATA::buf_nazwisko, DATA::buf_nazwisko.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_email", "Email", DATA::buf_email, DATA::buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    int step = 1, stepf = 5;
    if(ImGui::InputScalarN("##test4", ImGuiDataType_U32, (void*)DATA::buf_data, 3, &step, &stepf))
    {
        if(DATA::buf_data[0] > 31u) { DATA::buf_data[0] = 31u; }
        else if(DATA::buf_data[0] < 1u) { DATA::buf_data[0] = 1u; }
        if(DATA::buf_data[1] > 12u) { DATA::buf_data[1] = 12u; }
        else if(DATA::buf_data[1] < 1u) { DATA::buf_data[1] = 1u; }
        if(DATA::buf_data[2] > 2022u) { DATA::buf_data[2] = 2022u; }
        else if(DATA::buf_data[2] < 1900u) { DATA::buf_data[2] = 1900u; }
    }
    ImGui::SameLine(); ImGui::Text("date(dd-mm-yyyy)");

    ImGui::InputTextWithHint("##bin_stud_miejscezam", "Miejsce zamieszkania", DATA::buf_miejscezam, DATA::buf_miejscezam.size());
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_stud_plec", "Plec", DATA::buf_plec, DATA::buf_plec.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(16)");

    ImGui::InputTextWithHint("##bin_stud_imieojca", "Imie Ojca", DATA::buf_imieojca, DATA::buf_imieojca.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_imiematki", "Imie Matki", DATA::buf_imiematki, DATA::buf_imiematki.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_stopien", "Stopien studiow", DATA::buf_stopien, DATA::buf_stopien.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;
    
    std::stringstream query;
    query << "INSERT INTO prj.student (nr_albumu, imie, drugie_imie, nazwisko, email, data_urodzenia) values ("
        << DATA::buf_id.toInt() << ", "
        << std::quoted(DATA::buf_imie.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_drugieimie.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_nazwisko.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_email.getBuffer(), '\'') << ", "
        << "TO_DATE('" << DATA::buf_data[0] << "."
            << DATA::buf_data[1] << "."
            << DATA::buf_data[2] << "'"
        << ", 'DD.MM.YYYY'));";
    
    if((DATA::buf_miejscezam != 0)
    || (DATA::buf_plec != 0)
    || (DATA::buf_imieojca != 0)
    || (DATA::buf_imiematki != 0))
    {
        query << "INSERT INTO prj.student_informacje (nr_albumu, miejsce_zamieszkania, plec, imie_ojca, imie_matki) values ("
            << DATA::buf_id.toInt() << ", "
            << std::quoted(DATA::buf_miejscezam.getBuffer(), '\'') << ", "
            << std::quoted(DATA::buf_plec.getBuffer(), '\'') << ", "
            << std::quoted(DATA::buf_imieojca.getBuffer(), '\'') << ", "
            << std::quoted(DATA::buf_imiematki.getBuffer(), '\'') << ");"; 
    }

    if(DATA::buf_stopien.length() != 0)
    {
        tryConnect(str.str().c_str());
        chooseFromQuery("SELECT id_kierunek, nazwa, stopien FROM prj.kierunek WHERE stopien = "+DATA::buf_stopien.toString()+" ORDER BY 1;", "Wybierz kierunek:", 1);
    }

    if(DATA::current_choice > 0)
    {
        auto ID = (DATA::qresult[DATA::current_choice-1]["id_kierunek"]).as<int>();
        query << "INSERT INTO prj.student_kierunek (id_kierunek, skrot_nazwy, nr_albumu, data_rozpoczecia, data_zakonczenia) values ("
            << ID << ", "
            << "(SELECT skrot_nazwy FROM prj.kierunek WHERE id_kierunek = " << ID << "), "
            << DATA::buf_id.toInt() << ", "
            << "(SELECT TO_DATE(CURRENT_TIMESTAMP::VARCHAR, 'YYYY-MM-DD')), "
            << "TO_DATE('2077-5-22', 'YYYY-MM-DD'));";
        std::cout << query.str() << std::endl;
    }
    // SELECT TO_DATE(CURRENT_TIMESTAMP::VARCHAR, 'YYYY-MM-DD');  // wez aktualna date

    auto filled = (DATA::buf_id != 0)
        && (DATA::buf_imie.length() != 0)
        && (DATA::buf_drugieimie.length() != 0)
        && (DATA::buf_nazwisko.length() != 0)
        && (DATA::buf_email.length() != 0);

    if(filled)
    {
        submitButton(str.str(), query.str());
    }
    if(DATA::query_failed)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}
