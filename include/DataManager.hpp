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

    static InputBuffer<32> buf_imie;
    static InputBuffer<32> buf_drugieimie;
    static InputBuffer<32> buf_nazwisko;
    static InputBuffer<64> buf_email;

    static InputBuffer<64> buf_nazwa;
    static InputBuffer<16> buf_semestr;
    static InputBuffer<16> buf_ects;
    static InputBuffer<16> buf_miejsca;
    static bool buf_egzamin = false;
    static InputBuffer<16> buf_typ;
    static InputBuffer<1024> buf_opis;

    static InputBuffer<16> buf_dataurodzin;  // format: YYYY-MM-DD
    static InputBuffer<64> buf_miejscezam;
    static InputBuffer<16> buf_plec;
    static InputBuffer<32> buf_imieojca;
    static InputBuffer<32> buf_imiematki;

    static pqxx::result query_result;

    static auto result = false;
    static auto clicked = false;
    static std::exception exc;

    static bool should_clear = false;
    [[maybe_unused]] static void CLEAR()
    {
        // buf_host = "";
        // buf_port = "";
        // buf_dbname = "";
        // buf_user = "";
        // buf_password = "";

        buf_imie = "";
        buf_drugieimie = "";
        buf_nazwisko = "";
        buf_email = "";

        buf_nazwa = "";
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

        query_result.clear();
        result = false;
        clicked = false;
        exc = {};

        should_clear = false;
    }
}