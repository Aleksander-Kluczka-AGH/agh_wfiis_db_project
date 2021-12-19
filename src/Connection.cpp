#include "../include/Connection.hpp"

// void tryConnect(const char* connection_string, const std::size_t count)
// {
//     if(!DATA::is_conn && DATA::tries < count)
//     {
//         try
//         {
//             std::cout << "trying! " << DATA::tries << std::endl;
//             DATA::connection = std::make_unique<pqxx::connection>(connection_string);
//             if(!DATA::connection->is_open())
//             {
//                 DATA::tries++;
//             }
//         }
//         catch(const std::exception& e)
//         {
//             DATA::exception_message = e.what();
//             std::cout << e.what() << std::endl;
//             DATA::connection.reset(nullptr);
//             DATA::tries++;
//         }
//     }
// }


// Connection::Connection()
// :
// m_buffer("host=localhost dbname=u9kluczka user=u9kluczka password=9kluczka sslmode=allow"),
// m_connection(nullptr),
// m_work(nullptr)
// { }

// Connection::Connection(const std::string& host, const std::string& dbname, const std::string& user, const std::string& password, const std::string& sslmode) noexcept
// :
// m_buffer("host="+host+" dbname="+dbname+" user="+user+" password="+password+" sslmode="+sslmode),
// m_connection(nullptr),
// m_work(nullptr)
// {
//     try
//     {
//         m_connection = new pqxx::connection(m_buffer.c_str());
//     }
//     catch(const std::exception& e)
//     {
//         std::cout << "CONNECTION EXCEPTION: " << e.what() << std::endl;
//         if(m_connection)
//         {
//             delete m_connection;
//             m_connection = nullptr;
//         }
//     }
// }

// Connection::~Connection()
// {
//     m_buffer.clear();
//     if(m_connection)
//     {
//         m_connection->close();
//         delete m_connection;
//     }
//     if(m_work)
//     {
//         m_work->abort();
//         delete m_work;
//         m_work = nullptr;
//     }
//     m_result.clear();
// }

// void Connection::init(const std::string& host, const std::string& dbname, const std::string& user, const std::string& password, const std::string& sslmode) noexcept
// {
//     if(m_connection)
//     {
//         m_connection->close();
//         delete m_connection;
//         m_connection = nullptr;
//     }
//     this->reset();

//     m_buffer = "host="+host+" dbname="+dbname+" user="+user+" password="+password+" sslmode="+sslmode;
//     try
//     {
//         m_connection = new pqxx::connection(m_buffer.c_str());
//     }
//     catch(const std::exception& e)
//     {
//         std::cout << "CONNECTION EXCEPTION: " << e.what() << std::endl;
//         if(m_connection)
//         {
//             delete m_connection;
//             m_connection = nullptr;
//         }
//     }
// }

// void Connection::reset() noexcept
// {
//     m_buffer.clear();
//     if(m_work)
//     {
//         m_work->abort();
//         delete m_work;
//         m_work = nullptr;
//     }
//     m_result.clear();
// }

// bool Connection::check() const noexcept
// {
//     bool res;
//     try
//     {
//         if(m_connection)
//         {
//             res = m_connection->is_open();
//         }
//         else
//         {
//             res = false;;
//         }
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//         return false;
//     }
//     return res;
// }

// bool Connection::hasResults() const noexcept
// {
//     return !m_result.empty();
// }

// bool Connection::executeQuery(const std::string& query) noexcept
// {
//     std::cout << query << std::endl;
//     m_result.clear();
//     if(!m_connection)
//     {
//         return false;
//     }
//     if(!m_connection->is_open())
//     {
//         return false;
//     }
//     else
//     {
//         try
//         {
//             if(!m_work)
//             {
//                 m_work = new pqxx::work{*m_connection};
//             }
//             auto res = pqxx::result{m_work->exec(query.c_str())};
//             m_result.swap(res);
//             delete m_work;
//             m_work = nullptr;
//         }
//         catch(const std::exception& e)
//         {
//             std::cout << "QUERY EXCEPTION: " << e.what() << std::endl;
//             std::cout << "CONTENT: " << m_result.size() << std::endl;
//             return false;
//         }
//         return true;
//     }
// }

// const pqxx::result& Connection::getResult() const noexcept
// {
//     return m_result;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void getQueryResult(const std::string& query, bool debug)
// {
//     try  // Connect to the database.
//     {
//         char buffer[1024];
//         std::sprintf(buffer, "host=%s dbname=%s user=%s password=%s sslmode=allow",
//             DATA::buf_host.getBuffer(),
//             DATA::buf_dbname.getBuffer(),
//             DATA::buf_user.getBuffer(),
//             DATA::buf_password.getBuffer());
//         pqxx::connection C(buffer);
//         if(!C.is_open())
//         {
//             throw std::runtime_error("Connection is not open");
//         }

//         pqxx::work W{C};  // Start a transaction.

//         auto res = pqxx::result{W.exec(query.c_str())};
//         DATA::query_result.swap(res);  // Perform a query and retrieve all results.
//     }
//     catch (const std::exception& e)
//     {
//         std::cout << "QUERY EXCEPTION: " << e.what() << std::endl;
//         std::cout << "CONTENT: " << DATA::query_result.size() << std::endl;
//         DATA::result = false;
//         return;
//     }

//     if(debug)
//     {
//         if(!DATA::query_result.empty())
//         {
//             std::cout << "QUERY SIZE: " << DATA::query_result.size() << std::endl;
//             for(auto row : DATA::query_result)
//             {
//                 for(auto el : row)
//                 {
//                     std::cout << el << " ";
//                 }
//                 std::cout << std::endl;
//             }
//         }
//         else
//         {
//             std::cout << "QUERY DEBUG: Can't print anything, because size = " << DATA::query_result.size() << std::endl;
//         }
//     }

//     DATA::result = true;
//     return;
// }
