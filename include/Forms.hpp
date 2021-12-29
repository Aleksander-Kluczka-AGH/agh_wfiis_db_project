#pragma once

#include "Connection.hpp"
#include "Util.hpp"

/**
 * @brief Connection testing form
 */
void formConnection();

/**
 * @brief Information section for the end user
 */
void formInfo();

/**
 * @brief The form for a new faculty
 */
void formInputWydzial();

/**
 * @brief The form for a new field
 */
void formInputKierunek();

/**
 * @brief The form for a new professor
 */
void formInputProwadzacy();

/**
 * @brief The form for a new subject
 */
void formInputPrzedmiot();

/**
 * @brief The registration form for a new student
 */
void formInputStudent();

/**
 * @brief The list of basic database statistics
 */
void formOutputAll();

/**
 * @brief The list of known fields
 */
void formOutputKierunek();

/**
 * @brief The list of known professors
 */
void formOutputProwadzacy();

/**
 * @brief The list of known subjects
 */
void formOutputPrzedmiot();

/**
 * @brief The list of known students
 */
void formOutputStudent();

/**
 * @brief The list of known faculties
 */
void formOutputWydzial();

/**
 * @brief The student registration forms for elective subjects
 */
void formRegisterStudentPrzedmiot();
