#pragma once

#include "Root.hpp"
#include "InputBuffer.hpp"

namespace DATA
{
    static InputBuffer<128> buf_host = "localhost";
    static InputBuffer<8> buf_port = "5432";
    static InputBuffer<64> buf_dbname = "u9kluczka";
    static InputBuffer<64> buf_user = "u9kluczka";
    static InputBuffer<64> buf_password = "9kluczka";

    static InputBuffer<8> buf_id;
    static InputBuffer<32> buf_imie;
    static InputBuffer<32> buf_drugieimie;
    static InputBuffer<32> buf_nazwisko;
    static InputBuffer<64> buf_email;

    static InputBuffer<64> buf_nazwa;
    static InputBuffer<8> buf_skrotnazwy;
    static InputBuffer<16> buf_semestr;
    static InputBuffer<16> buf_ects;
    static InputBuffer<16> buf_miejsca;
    static bool buf_egzamin = false;
    static InputBuffer<16> buf_typ;
    static InputBuffer<1024> buf_opis;
    static InputBuffer<16> buf_prog;  // score bar

    static InputBuffer<16> buf_dataurodzin;  // format: YYYY-MM-DD
    static InputBuffer<64> buf_miejscezam;
    static InputBuffer<16> buf_plec;
    static InputBuffer<32> buf_imieojca;
    static InputBuffer<32> buf_imiematki;

    static InputBuffer<16> buf_stopien;
    static unsigned buf_data[3] = {1u, 1u, 2000u};

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    static std::unique_ptr<pqxx::connection> connection = nullptr;
    // static std::unique_ptr<pqxx::work> work = nullptr;
    static pqxx::result qresult;
    static auto is_conn = false;
    static auto has_results = false;
    static auto requested_results = false;
    static auto query_failed = false;
    static InputBuffer<256> buf_error;
    static InputBuffer<64> buf_label;
    static int current_choice = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static std::size_t tries = 0;
    static std::string exception_message;

    static bool should_clear = false;
    [[maybe_unused]] static void CLEAR()
    {
        std::cout << "CLEAR()" << std::endl;

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
        connection.reset(nullptr);
        qresult.clear();
        is_conn = false;
        has_results = false;
        requested_results = false;
        current_choice = 0;

        tries = 0;
        exception_message.clear();

        should_clear = false;
    }
}