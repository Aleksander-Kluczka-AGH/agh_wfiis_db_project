#include "../include/InputBuffer.hpp"
#include "../include/Util.hpp"

void formInputPrzedmiot()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY PRZEDMIOT");
    ImGui::NewLine();

    InputBuffer<64> buf_nazwa;
    InputBuffer<16> buf_semestr;
    InputBuffer<16> buf_ects;
    InputBuffer<16> buf_miejsca;
    bool buf_egzamin = false;
    InputBuffer<16> buf_typ;
    InputBuffer<1024> buf_opis;

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_prze_nazwa", "Nazwa", buf_nazwa, buf_nazwa.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_prze_semestr", "Numer semestru", buf_semestr, buf_semestr.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_prze_ects", "Liczba punktow ECTS", buf_ects, buf_ects.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_prze_miejsca", "Liczba miejsc", buf_miejsca, buf_miejsca.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::Checkbox("Egzamin", &buf_egzamin);

    ImGui::InputTextWithHint("##bin_prze_typ", "Typ przedmiotu (obowiazkowy/obieralny)", buf_typ, buf_typ.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(16)");

    ImGui::InputTextMultilineWithHint("##bin_prze_opis", "Opis", buf_opis, buf_opis.size(), sf::Vector2f(0.f, 300.f));
    ImGui::SameLine(); ImGui::Text("varchar(1024)");
}
