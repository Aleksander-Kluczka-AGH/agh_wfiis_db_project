#include "../include/Forms.hpp"

void formRegisterStudentPrzedmiot()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "REJESTRACJA NA PRZEDMIOTY OBIERALNE");
    ImGui::NewLine();

    InputBuffer<32> buf_nazwisko;
    InputBuffer<64> buf_email;

    auto flags = ImGuiInputTextFlags_CharsNoBlank;

    ImGui::InputTextWithHint("##breg_stpr_nazwisko", "Nazwisko", buf_nazwisko, buf_nazwisko.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##breg_stpr_email", "Email", buf_email, buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    // TODO: 
    // - Request do bazy po liste przedmiotow obieralnych
    // - Wyswietlenie listy przedmiotow
    // - Dodawanie przedmiotow do *jakiegos* bufora
    // - Listowanie wybranych przedmiotow ponizej
    // - Dodanie pozycji za kazdy wybrany przedmiot
    // + Sprawdzenie, czy zgadza sie liczba ECTS
}
