#include "../include/DataManager.hpp"

namespace hidden
{
    meta::meta()
    :
    qresult{},
    is_conn{false},
    has_results{false},
    requested_results{false},
    query_failed{false},
    buf_error{},
    buf_label{},
    current_choice{0}
    { }

    void meta::reset() noexcept
    {
        qresult.clear();
        is_conn = false;
        has_results = false;
        requested_results = false;
        current_choice = 0;
    }
}

namespace DATA
{
    InputBuffer<128> buf_host = "localhost";
    InputBuffer<8> buf_port = "5432";
    InputBuffer<64> buf_dbname = "u9kluczka";
    InputBuffer<64> buf_user = "u9kluczka";
    InputBuffer<64> buf_password = "9kluczka";

    InputBuffer<8> buf_id{};
    InputBuffer<32> buf_imie{};
    InputBuffer<32> buf_drugieimie{};
    InputBuffer<32> buf_nazwisko{};
    InputBuffer<64> buf_email{};

    InputBuffer<64> buf_nazwa;
    InputBuffer<8> buf_skrotnazwy;
    InputBuffer<16> buf_semestr;
    InputBuffer<16> buf_ects;
    InputBuffer<16> buf_miejsca;
    bool buf_egzamin = false;
    InputBuffer<16> buf_typ;
    InputBuffer<1024> buf_opis;
    InputBuffer<16> buf_prog;  // score bar

    InputBuffer<16> buf_dataurodzin;  // format: YYYY-MM-DD
    InputBuffer<64> buf_miejscezam;
    InputBuffer<16> buf_plec;
    InputBuffer<32> buf_imieojca;
    InputBuffer<32> buf_imiematki;

    InputBuffer<16> buf_stopien;
    unsigned buf_data[3] = {1u, 1u, 2000u};

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    hidden::meta one;
    hidden::meta two;
    std::unique_ptr<pqxx::connection> connection = nullptr;

    pqxx::result& qresult = one.qresult;
    bool& is_conn = one.is_conn;
    bool& has_results = one.has_results;
    bool& requested_results = one.requested_results;
    bool& query_failed = one.query_failed;
    InputBuffer<256>& buf_error = one.buf_error;
    InputBuffer<64>& buf_label = one.buf_label;
    int& current_choice = one.current_choice;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t tries = 0;
    std::string exception_message;

    bool should_clear = false;
    void CLEAR()
    {
        static std::size_t iter = 1;
        std::cout << "CLEAR(" << iter++ << ")" << std::endl;

        // buf_host = "";
        // buf_port = "";
        // buf_dbname = "";
        // buf_user = "";
        // buf_password = "";

        buf_id = "";
        buf_imie = "";
        buf_drugieimie = "";
        buf_nazwisko = "";
        buf_email = "";

        buf_nazwa = "";
        buf_skrotnazwy = "";
        buf_semestr = "";
        buf_ects = "";
        buf_miejsca = "";
        buf_egzamin = "";
        buf_typ = "";
        buf_opis = "";
        buf_prog = "";

        buf_dataurodzin = "";
        buf_miejscezam = "";
        buf_plec = "";
        buf_imieojca = "";
        buf_imiematki = "";

        buf_stopien = "";
        buf_data[0] = 1u; buf_data[1] = 1u; buf_data[2] = 2000u;

        if(connection && connection->is_open())
        {
            connection->close();
        }
        connection = nullptr;

        one.reset();
        two.reset();

        tries = 0;
        // exception_message.clear();

        should_clear = false;
    }
}
