void formInputProwadzacy()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY PROWADZACY");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_prow_imie", "Imie", DATA::buf_imie, DATA::buf_imie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_prow_drugieimie", "Drugie imie", DATA::buf_drugieimie, DATA::buf_drugieimie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_prow_nazwisko", "Nazwisko", DATA::buf_nazwisko, DATA::buf_nazwisko.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");
    
    ImGui::InputTextWithHint("##bin_prow_email", "Email", DATA::buf_email, DATA::buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    // TODO:
    // - Request do bazy danych o liste przedmiotow bez przypisanego prowadzacego
    //   = jesli nie ma zadnego przedmiotu, odeslij do formularza na przedmiot
    // - Wyswietl liczbe przedmiotow

    const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD"};
    static const char* current_item = "Wolne przedmioty: ";
    if (ImGui::BeginCombo("##bin_prow_przedmiot", current_item))
    {
        for (auto& it : items)
        {
            if(ImGui::Selectable(it, (current_item == it))) { current_item = it; }
        }
        ImGui::EndCombo();
    }
}
