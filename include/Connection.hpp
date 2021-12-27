#pragma once

#include "DataManager.hpp"

static void tryConnect(const char* connection_string, const std::size_t count = 3);
static void sendQuery(const std::string& query, const std::size_t& qrid = 1);
static void resetConnection();
static void chooseFromQuery(const std::string& query, const std::string& init_label = "Wybierz", const std::size_t& column_label = 0, const std::size_t& qrid = 1, const std::string& unique_id = "##Submit");
static void comboFromQuery(const std::size_t& column_label, const std::size_t& qrid = 1, const std::string& unique_id = "##Submit");
static void submitButton(const std::string& connection, const std::string& query);
static void tableFromQuery(const std::string& query, const std::vector<std::size_t>& columns);

// this shit below is the only signature that works, it has to be static and has to be defined here
// why? I have no clue whatsoever
// otherwise the connection is not established correctly >:(
[[maybe_unused]]
static void tryConnect(const char* connection_string, const std::size_t count)
{
    if(!DATA::one.is_conn && DATA::tries < count)
    {
        try
        {
            DATA::connection = std::make_unique<pqxx::connection>(connection_string);
            if(!DATA::connection->is_open())
            {
                DATA::tries++;
            }
            else
            {
                DATA::one.is_conn = true;
                DATA::two.is_conn = true;
                return;
            }
        }
        catch(const std::exception& e)
        {
            DATA::one.is_conn = false;
            DATA::two.is_conn = false;
            DATA::exception_message = e.what();
            DATA::connection.reset(nullptr);
            DATA::tries++;
            std::cout << e.what() << std::endl;
        }
    }
}

[[maybe_unused]]
static void sendQuery(const std::string& query, const std::size_t& qrid)
{
    // std::cout << __PRETTY_FUNCTION__ << '\n';
    auto temp = std::ref(DATA::one);
    if(qrid == 2)
    {
        temp = std::ref(DATA::two);
        // std::cout << "going with TWO\n";
    }
    int& sel = temp.get().current_choice;
    // std::cout << "current_choice = " << sel << '\n';
    if(DATA::connection && DATA::connection->is_open())
    {
        // std::cout << "connection open\n";
        temp.get().is_conn = true;
        if(!temp.get().requested_results && DATA::tries < 3)
        {
            // std::cout << "requesting results... attempt " << DATA::tries << '\n';
            try
            {
                temp.get().requested_results = true;
                pqxx::work W{*DATA::connection};
                auto res = W.exec(query.c_str());
                W.commit();
                // std::cout << "commiting work, query = '" << query << "'\n result size = " << res.size() << '\n';
                temp.get().qresult.swap(res);
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << '\n';
                temp.get().buf_error = e.what();
                DATA::tries++;
                sel = -1;
                return;
            }

            temp.get().has_results = !temp.get().qresult.empty();
            // std::cout << "finishing... has_result = " << temp.get().has_results << ", requested_result = " << temp.get().requested_results << '\n';
        }
    }
    else
    {
        // do not show submit button if connection is not established
        ImGui::TextColored(sf::Color::Red, "Nie udalo sie nawiazac polaczenia.");
        ImGui::TextColored(sf::Color::Red, "Szczegoly: ");
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
        sel = -1;
    }
}

[[maybe_unused]]
static void resetConnection()
{
    DATA::one.is_conn = false;
    DATA::two.is_conn = false;
    DATA::tries = 0;
    if(DATA::connection)
    {
        DATA::connection->close();
        DATA::connection = nullptr;
    }
}

[[maybe_unused]]
static void chooseFromQuery(
    const std::string& query,
    const std::string& init_label,
    const std::size_t& column_label,
    const std::size_t& qrid,
    const std::string& unique_id)
{
    auto temp = std::ref(DATA::one);
    if(qrid == 2)
    {
        temp = std::ref(DATA::two);
    }
    if(temp.get().is_conn)
    {
        if(!temp.get().requested_results) { temp.get().buf_label = init_label.c_str(); }
        sendQuery(query, qrid);
    }
    comboFromQuery(column_label, qrid, unique_id);
}

[[maybe_unused]]
static void comboFromQuery(const std::size_t& column_label, const std::size_t& qrid, const std::string& unique_id)
{
    // std::cout << __PRETTY_FUNCTION__ << '\n';
    auto temp = std::ref(DATA::one);
    // std::cout << "address ONE = " << &DATA::one << '\n';
    // std::cout << "address TWO = " << &DATA::two << '\n';
    // std::cout << "address temp = " << &temp.get() << '\n';
    if(qrid == 2)
    {
        temp = std::ref(DATA::two);
        // std::cout << "going with TWO\n";
        // std::cout << "address inside = " << &temp.get() << '\n';

    }
    // std::cout << "address outside = " << &temp.get() << '\n';
    if(temp.get().requested_results && temp.get().has_results)
    {
        // std::cout << "requested and obtained results\n";
        // std::cout << "result size = " << temp.get().qresult.size() << '\n';
        if(ImGui::BeginCombo(unique_id.c_str(), temp.get().buf_label.getBuffer()))
        {
            // std::cout << "inside the combo!\n";
            auto iter = 1;
            for(auto row : temp.get().qresult)
            {
                std::stringstream ss;
                for(auto col : row) { ss << col << "  "; }

                if(ImGui::Selectable(ss.str().c_str()))  // if currently selected
                {
                    temp.get().buf_label = row[column_label].c_str();  // use buffer to preview current choice
                    temp.get().current_choice = iter;
                    // std::cout << "selected '" << temp.get().buf_label << "', current_choice = " << temp.get().current_choice << '\n';
                }
                iter++;
            }
            ImGui::EndCombo();
        }
    }
    else if(!temp.get().has_results)
    {
        ImGui::TextWrapped("Nie otrzymano wynikow zwrotnych.");
        temp.get().current_choice = -1;
    }
    // std::cout << '\n';
}

[[maybe_unused]]
static void submitButton(const std::string& connection, const std::string& query)
{
    if(ImGui::Button("Wyslij"))
    {
        resetConnection();
        tryConnect(connection.c_str());
        if(DATA::is_conn)
        {
            try
            {
                pqxx::work W{*DATA::connection};
                auto res = W.exec0(query.c_str());
                W.commit();
                DATA::query_failed = false;
            }
            catch(const std::exception& e)
            {
                DATA::CLEAR();
                DATA::query_failed = true;
                DATA::exception_message = e.what();
                std::cout << e.what() << std::endl;
            }
            if(!DATA::query_failed)
            {
                DATA::CLEAR();
            }
        }
    }
}

[[maybe_unused]]
static void tableFromQuery(const std::string& query, const std::vector<std::size_t>& columns)
{
    if(DATA::is_conn)
    {
        sendQuery(query);
    }

    const auto size = static_cast<std::size_t>(DATA::qresult.columns());
    const auto count = std::count_if(columns.begin(), columns.end(), [&size](const std::size_t& el) { return (el <= size) && (el > 0); });

    if(DATA::requested_results && DATA::has_results)
    {
        if(ImGui::BeginTable("##table", count, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg))
        {
            for(auto& col : columns)
            {
                if((col > size) || (col < 1)) { continue; }
                ImGui::TableSetupColumn(DATA::qresult.column_name(col-1));
            }
            ImGui::TableHeadersRow();

            for(auto row : DATA::qresult)
            {
                ImGui::TableNextRow();
                for(auto& col : columns)
                {
                    if((col > size) || (col < 1)) { continue; }
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", row[col-1].c_str());
                }
            }
            ImGui::EndTable();
        }
    }
    else if(!DATA::has_results)
    {
        ImGui::TextWrapped("Nie otrzymano wynikow zwrotnych.");
    }
}