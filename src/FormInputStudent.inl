void formInputStudent()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY STUDENT");
    ImGui::NewLine();    

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_stud_imie", "Imie", DATA::buf_imie, DATA::buf_imie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_drugieimie", "Drugie imie", DATA::buf_drugieimie, DATA::buf_drugieimie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_nazwisko", "Nazwisko", DATA::buf_nazwisko, DATA::buf_nazwisko.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_email", "Email", DATA::buf_email, DATA::buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    // TODO: ZAMIEN NA 3 POLA ZBIERAJACE 1-31, 1-12, 1900-2022
    // ImGui::InputTextWithHint("##bin_stud_dataurodzin", "Data urodzin", DATA::buf_typ, DATA::buf_typ.size(), flags);
    // ImGui::SameLine(); ImGui::Text("varchar(16)");

    ImGui::InputTextWithHint("##bin_stud_miejscezam", "Miejsce zamieszkania", DATA::buf_miejscezam, DATA::buf_miejscezam.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_stud_plec", "Plec", DATA::buf_plec, DATA::buf_plec.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(16)");

    ImGui::InputTextWithHint("##bin_stud_imieojca", "Imie Ojca", DATA::buf_imieojca, DATA::buf_imieojca.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_imiematki", "Imie Matki", DATA::buf_imiematki, DATA::buf_imiematki.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    // TODO:
    // - Wybranie stopnia studiow (1-2)
    // - Pobranie z bazy danych listy kierunkow
    // - Przefiltrowanie kierunkow, ktore sa na innym stopniu
    // - Przefiltrowanie kierunkow, ktore nie maja wolnych miejsc
    // - Wybieranie kierunku z listy
}
