#include "../include/Util.hpp"

void formInputPrzedmiot()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY PRZEDMIOT");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_prze_nazwa", "Nazwa", DATA::buf_nazwa, DATA::buf_nazwa.size(), flags);
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

    // TODO:
    // - Dodanie pola wybierajacego stopien studiow
    // - Request do bazy danych po liste kierunkow
    // - Wybieranie kierunku z listy
}
