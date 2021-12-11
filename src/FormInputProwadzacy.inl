#include "../include/InputBuffer.hpp"

void formInputProwadzacy()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY PROWADZACY");
    ImGui::NewLine();

    InputBuffer<32> buf_imie;
    InputBuffer<32> buf_drugieimie;
    InputBuffer<32> buf_nazwisko;
    InputBuffer<64> buf_email;

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_prow_imie", "Imie", buf_imie, buf_imie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_prow_drugieimie", "Drugie imie", buf_drugieimie, buf_drugieimie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_prow_nazwisko", "Nazwisko", buf_nazwisko, buf_nazwisko.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");
    
    ImGui::InputTextWithHint("##bin_prow_email", "Email", buf_email, buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    // wyslij do bazy zapytanie o liste przedmiotow bez prowadzacego
    // - jesli nie ma zadnego, odeslij do formularza na nowy przedmiot
    // - wyswietl przedmioty

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
