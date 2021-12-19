#include "../include/Forms.hpp"

void formOutputKierunek()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA KIERUNKOW");
    ImGui::NewLine();

    // try
    // {
    //     Connection C(
    //         DATA::buf_host.getBuffer(),
    //         DATA::buf_dbname.getBuffer(),
    //         DATA::buf_user.getBuffer(),
    //         DATA::buf_password.getBuffer());
    //     // pqxx::connection C(buffer);
    //     if(!C.check())
    //     {
    //         throw std::runtime_error("Connection is not open");
    //     }
    //     if(C.executeQuery("SELECT * FROM lab04.uczestnik"))
    //     {
    //         if(ImGui::BeginTable("##output_kierunek", 3, ImGuiTableFlags_Borders))
    //         {
    //             auto& res = C.getResult();
    //             for(auto row : res)
    //             {
    //                 // ImGui::TableNextRow();
    //                 ImGui::TableNextColumn(); ImGui::Text("%s", row["id_uczestnik"].c_str());
    //                 ImGui::TableNextColumn(); ImGui::Text("%s", row["imie"].c_str());
    //                 ImGui::TableNextColumn(); ImGui::Text("%s", row["nazwisko"].c_str());
    //             }
    //             ImGui::EndTable();
    //         }
    //     }
    // }
    // catch (const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    //     // return 1;
    // }
}
