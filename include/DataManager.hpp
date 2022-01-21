#pragma once

#include "InputBuffer.hpp"

namespace hidden
{
    /**
     * @brief Wrapper around query results and its flags
     */
    struct meta final
    {
        /**
         * @brief Default constructor
         */
        meta();

        /**
         * @brief Copy assignment operator (set to default)
         * 
         * @return The reference to itself
         */
        meta& operator=(const meta&) = default;

        /**
         * @brief Resets all members to their defautl values
         * 
         * It does not reset query_failed, buf_error, buf_label
         */
        void reset() noexcept;

        pqxx::result qresult; /**< The vector of query results, empty by default */
        bool is_conn; /**< Is the connection established? default: false */
        bool has_results; /**< Does the qresult have any contents? default: false */
        bool requested_results; /**< Were the results requested? default: false */
        bool query_failed; /**< Did the query fail? */
        InputBuffer<256> buf_error; /**< The buffer for query error messages */
        InputBuffer<64> buf_label; /**< The buffer for ImGui labels */
        int current_choice; /**< The currently selected dropdown list choice */
    };
}

namespace ROOT
{ // DONT TOUCH THIS STUFF
    extern bool success_at_first_try;
}


namespace DATA
{
    extern InputBuffer<128> buf_host; /**< The buffer for a host string */
    extern InputBuffer<8> buf_port; /**< The buffer for a port number */
    extern InputBuffer<64> buf_dbname; /**< The buffer for a database name */
    extern InputBuffer<64> buf_user; /**< The buffer for a databse username */
    extern InputBuffer<64> buf_password; /**< The buffer for a username password */

    extern InputBuffer<8> buf_id; /**< The buffer for any ID */
    extern InputBuffer<32> buf_imie; /**< The buffer for a first name */
    extern InputBuffer<32> buf_drugieimie; /**< The buffer for an extra name */
    extern InputBuffer<32> buf_nazwisko; /**< The buffer for a last name */
    extern InputBuffer<64> buf_email; /**< The buffer for an email address */

    extern InputBuffer<64> buf_nazwa; /**< The buffer for any custom name */
    extern InputBuffer<8> buf_skrotnazwy; /**< The buffer for an abbreviation */
    extern InputBuffer<16> buf_semestr; /**< The buffer for a semester number */
    extern InputBuffer<16> buf_ects; /**< The buffer for ECTS points */
    extern InputBuffer<16> buf_miejsca; /**< The buffer for a total slots count */
    extern bool buf_egzamin; /**< The buffer for a final exam flag */
    extern InputBuffer<16> buf_typ; /**< The buffer for a type */
    extern InputBuffer<1024> buf_opis; /**< The buffer for a description */
    extern InputBuffer<16> buf_prog; /**< The buffer for a score bar */

    extern InputBuffer<16> buf_dataurodzin; /**< The buffer for a date of birth, format: YYYY-MM-DD */
    extern InputBuffer<64> buf_miejscezam; /**< The buffer for a domicile */
    extern InputBuffer<16> buf_plec; /**< The buffer for a gender */
    extern InputBuffer<32> buf_imieojca; /**< The buffer for a father's name */
    extern InputBuffer<32> buf_imiematki; /**< The buffer for a mother's name */

    extern InputBuffer<16> buf_stopien; /**< The buffer for a degree of study */
    extern unsigned buf_data[3]; /**< The buffer for a year, a month and a day, respectively */
    
    extern std::unique_ptr<pqxx::connection> connection; /**< The main connection handler */
    extern hidden::meta one; /**< The result buffer */
    extern hidden::meta two; /**< The second result buffer */

    // typedefs for compatibility because I am super lazy
    extern pqxx::result& qresult;
    extern bool& is_conn;
    extern bool& has_results;
    extern bool& requested_results;
    extern bool& query_failed;
    extern InputBuffer<256>& buf_error;
    extern InputBuffer<64>& buf_label;
    extern int& current_choice;

    extern std::size_t tries; /**< The number of current connection attempt count */
    extern std::string exception_message; /**< The buffer for any exception messages */

    extern bool should_clear; /**< The flag for reseting all of the buffers */
    
    /**
     * @brief Clears most flags and buffers
     */
    void CLEAR();
}
