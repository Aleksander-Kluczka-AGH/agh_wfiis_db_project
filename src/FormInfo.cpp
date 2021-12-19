#include "../include/Forms.hpp"

void formInfo()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "INFORMACJE");
    ImGui::NewLine();
    ImGui::Text("Witaj w interfejcie graficznym sluzacym do obslugi bazy danych przedmiotow obieralnych!");
    ImGui::Text("Uzywajac panelu po lewej stronie, wyswietl lub dodaj nowe informacje uzywajac formularzy.");
    ImGui::NewLine();
    ImGui::Text("Do tej informacji zawsze mozesz wrocic, klikajac przycisk \"Informacje\" w panelu.");
    ImGui::NewLine();
    ImGui::TextDisabled("Autor: Aleksander Kluczka");
}
