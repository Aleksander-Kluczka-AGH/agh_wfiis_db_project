#pragma once

#include "DataManager.hpp"

/**
 * @brief Try to connect to the PostgreSQL database
 * 
 * @param connection_string The string used to connect to the host
 * @param count The number of retries in case the connection was not established
 */
static void tryConnect(const char* connection_string, const std::size_t count = 3);

/**
 * @brief Send the @c query to the database
 * 
 * @param query The SQL query sent to the database
 * @param qrid The query ID, used to differentiate multiple queries in single section
 */
static void sendQuery(const std::string& query, const std::size_t& qrid = 1);

/**
 * @brief Reset the current connection
 * 
 * If the connection was already reset, this function does nothing.
 */
static void resetConnection();

/**
 * @brief Select the answer from dropdown list of @c query results
 * 
 * @param query The SQL query sent to the database
 * @param init_label The label initially set for the dropdown header
 * @param column_label The result's column number which content is to be displayed after selecting the answer
 * @param qrid The query ID, used to differentiate multiple queries in single section
 * @param unique_id The unique ID needed to satisfy the brokeness of ImGui
 */
static void chooseFromQuery(const std::string& query, const std::string& init_label = "Wybierz", const std::size_t& column_label = 0, const std::size_t& qrid = 1, const std::string& unique_id = "##Submit");

/**
 * @brief Draw dropdown list from global result vector
 * 
 * @param column_label The result's column number which content is to be displayed after selecting the answer
 * @param qrid The query ID, used to differentiate multiple queries in single section
 * @param unique_id The unique ID needed to satisfy the brokeness of ImGui
 */
static void comboFromQuery(const std::size_t& column_label, const std::size_t& qrid = 1, const std::string& unique_id = "##Submit");

/**
 * @brief Submit the @c query to the PostgreSQL database
 * 
 * @param connection The string used to connect to the host in case the conenction was not established
 * @param query The SQL query sent to the database
 */
static void submitButton(const std::string& connection, const std::string& query);

/**
 * @brief Draw table with @c query results
 * 
 * @param query The SQL query sent to the database
 * @param columns The list of columns from @c query which are to be displayed in the table
 */
static void tableFromQuery(const std::string& query, const std::vector<std::size_t>& columns);


[[maybe_unused]]
static void tryConnect(const char* connection_string, const std::size_t count)
{
    // this shit below is the only signature that works, it has to be static and has to be defined here
    // why? I have no clue whatsoever
    // otherwise the connection is not established correctly >:(
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
    auto temp = std::ref(DATA::one);
    if(qrid == 2) { temp = std::ref(DATA::two); }

    int& sel = temp.get().current_choice;
    if(DATA::connection && DATA::connection->is_open())
    {
        temp.get().is_conn = true;
        if(!temp.get().requested_results && DATA::tries < 3)
        {
            try
            {
                temp.get().requested_results = true;
                pqxx::work W{*DATA::connection};
                auto res = W.exec(query.c_str());
                W.commit();
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
    if(qrid == 2) { temp = std::ref(DATA::two); }

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
    auto temp = std::ref(DATA::one);
    if(qrid == 2) { temp = std::ref(DATA::two); }
    
    if(temp.get().requested_results && temp.get().has_results)
    {
        // sanity check
        auto safe_column_label = column_label;
        const auto size = static_cast<std::size_t>(temp.get().qresult.columns());
        if(safe_column_label >= size) { safe_column_label = size - 1; }  // we have results so size > 0

        if(ImGui::BeginCombo(unique_id.c_str(), temp.get().buf_label.getBuffer()))
        {
            auto iter = 1;
            for(auto row : temp.get().qresult)
            {
                std::stringstream ss;
                for(auto col : row) { ss << col << "  "; }

                if(ImGui::Selectable(ss.str().c_str()))  // if currently selected
                {
                    temp.get().buf_label = row[safe_column_label].c_str();  // use buffer to preview current choice
                    temp.get().current_choice = iter;
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
