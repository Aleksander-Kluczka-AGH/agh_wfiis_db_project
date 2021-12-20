#pragma once

#include "Root.hpp"
#include "DataManager.hpp"

// void tryConnect(const char* connection_string, const std::size_t count = 3);

// this shit below is the only signature that works, it has to be static and has to be defined here
// why? I have no clue whatsoever
// otherwise the connection is not established correctly >:(
[[maybe_unused]]
static void tryConnect(const char* connection_string, const std::size_t count = 3)
{
    if(!DATA::is_conn && DATA::tries < count)
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
                DATA::is_conn = true;
                return;
            }
        }
        catch(const std::exception& e)
        {
            DATA::is_conn = false;
            DATA::exception_message = e.what();
            DATA::connection.reset(nullptr);
            DATA::tries++;
            std::cout << e.what() << std::endl;
        }
    }
}

[[maybe_unused]]
static void resetConnection()
{
    DATA::is_conn = false;
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
    const std::string& init_label = "Wybierz",
    const std::size_t& column_label = 0,
    const std::string& unique_id = "##Submit")
{
    int& sel = DATA::current_choice;
    if(DATA::connection && DATA::connection->is_open())
    {
        DATA::is_conn = true;
        if(!DATA::requested_results && DATA::tries < 3)
        {
            try
            {
                DATA::requested_results = true;
                // DATA::work = std::make_unique<pqxx::work>(*DATA::connection);
                pqxx::work W{*DATA::connection};
                auto res = W.exec(query.c_str());
                W.commit();
                DATA::qresult.swap(res);
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                DATA::buf_error = e.what();
                DATA::tries++;
                sel = -1;
                return;
            }
            DATA::buf_label = init_label.c_str();
        }
        
        // the if below can be separated into a new function
        if(DATA::requested_results && !DATA::qresult.empty())
        {
            DATA::has_results = true;
            if(ImGui::BeginCombo(unique_id.c_str(), DATA::buf_label.getBuffer()))
            {
                auto iter = 1;
                for(auto row : DATA::qresult)
                {
                    std::stringstream ss;
                    for(auto col : row) { ss << col << "  "; }

                    if(ImGui::Selectable(ss.str().c_str()))  // if currently selected
                    {
                        DATA::buf_label = row[column_label].c_str();  // use buffer to preview current choice
                        sel = iter;
                    }
                    iter++;
                }
                ImGui::EndCombo();
            }
        }
        else
        {
            ImGui::TextWrapped("Nie otrzymano wynikow zwrotnych.");
            sel = -1;
        }
    }
    else
    {
        // do not show submit button if connection is not established
        ImGui::TextWrapped("Nie udalo sie nawiazac polaczenia.");
        ImGui::TextWrapped("Szczegoly: ");
        ImGui::TextWrapped("%s", DATA::exception_message.c_str());
        sel = -1;
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
                DATA::query_failed = true;
                DATA::exception_message = e.what();
                std::cout << e.what() << std::endl;
            }
        }
        DATA::CLEAR();
    }
}

// class Connection final
// {
//     public:
//     // "host=%s dbname=%s user=%s password=%s sslmode=allow"
//     Connection();
//     Connection(const std::string& host, const std::string& dbname, const std::string& user, const std::string& password, const std::string& sslmode = "allow") noexcept;
//     ~Connection();

//     void init(const std::string& host, const std::string& dbname, const std::string& user, const std::string& password, const std::string& sslmode = "allow") noexcept;
//     void reset() noexcept;
//     bool check() const noexcept;
//     bool hasResults() const noexcept;
//     bool executeQuery(const std::string& query) noexcept;
//     const pqxx::result& getResult() const noexcept;

//     private:
//     std::string m_buffer;  // buffer for psql query
//     pqxx::connection *m_connection;
//     pqxx::work *m_work;
//     pqxx::result m_result;
// };

// void getQueryResult(const std::string& query, bool debug = false);
