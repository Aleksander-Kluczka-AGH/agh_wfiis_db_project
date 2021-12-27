#pragma once

#include "InputBuffer.hpp"

namespace hidden
{
    struct meta final
    {
        meta();
        meta& operator=(const meta&) = default;
        void reset() noexcept;
        pqxx::result qresult;
        bool is_conn;
        bool has_results;
        bool requested_results;
        bool query_failed;
        InputBuffer<256> buf_error;
        InputBuffer<64> buf_label;
        int current_choice;
    };
}

namespace DATA
{
    extern InputBuffer<128> buf_host;
    extern InputBuffer<8> buf_port;
    extern InputBuffer<64> buf_dbname;
    extern InputBuffer<64> buf_user;
    extern InputBuffer<64> buf_password;

    extern InputBuffer<8> buf_id;
    extern InputBuffer<32> buf_imie;
    extern InputBuffer<32> buf_drugieimie;
    extern InputBuffer<32> buf_nazwisko;
    extern InputBuffer<64> buf_email;

    extern InputBuffer<64> buf_nazwa;
    extern InputBuffer<8> buf_skrotnazwy;
    extern InputBuffer<16> buf_semestr;
    extern InputBuffer<16> buf_ects;
    extern InputBuffer<16> buf_miejsca;
    extern bool buf_egzamin;
    extern InputBuffer<16> buf_typ;
    extern InputBuffer<1024> buf_opis;
    extern InputBuffer<16> buf_prog;  // score bar

    extern InputBuffer<16> buf_dataurodzin;  // format: YYYY-MM-DD
    extern InputBuffer<64> buf_miejscezam;
    extern InputBuffer<16> buf_plec;
    extern InputBuffer<32> buf_imieojca;
    extern InputBuffer<32> buf_imiematki;

    extern InputBuffer<16> buf_stopien;
    extern unsigned buf_data[3];

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    extern std::unique_ptr<pqxx::connection> connection;
    extern hidden::meta one;
    extern hidden::meta two;

    // typedefs for compatibility because I am super lazy
    extern pqxx::result& qresult;
    extern bool& is_conn;
    extern bool& has_results;
    extern bool& requested_results;
    extern bool& query_failed;
    extern InputBuffer<256>& buf_error;
    extern InputBuffer<64>& buf_label;
    extern int& current_choice;
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    extern std::size_t tries;
    extern std::string exception_message;

    extern bool should_clear;
    void CLEAR();
}
