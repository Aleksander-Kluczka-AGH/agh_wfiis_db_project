#pragma once

#include "Root.hpp"
#include "DataManager.hpp"
#include "InputBuffer.hpp"

inline void formInfo();
inline void formConnection();
inline void formInputAll();
inline void formInputPrzedmiot();
inline void formInputProwadzacy();
inline void formInputStudent();
inline void formRegisterStudentPrzedmiot();
inline void formOutputAll();
inline void formOutputPrzedmiot();
inline void formOutputProwadzacy();
inline void formOutputStudent();
inline void formOutputKierunek();

#include "../src/FormInfo.inl"
#include "../src/FormConnection.inl"
#include "../src/FormInputAll.inl"
#include "../src/FormInputPrzedmiot.inl"
#include "../src/FormInputProwadzacy.inl"
#include "../src/FormInputStudent.inl"
#include "../src/FormRegisterStudentPrzedmiot.inl"
#include "../src/FormOutputAll.inl"
#include "../src/FormOutputPrzedmiot.inl"
#include "../src/FormOutputProwadzacy.inl"
#include "../src/FormOutputStudent.inl"
#include "../src/FormOutputKierunek.inl"
