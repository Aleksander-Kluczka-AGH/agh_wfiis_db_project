#include "../include/Forms.hpp"

void formConnection()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "POLACZENIE Z BAZA DANYCH");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;

    ImGui::InputTextWithHint("##bcon_host", "Host", DATA::buf_host, DATA::buf_host.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(128)");

    ImGui::InputTextWithHint("##bcon_port", "Port", DATA::buf_port, DATA::buf_port.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("varchar(8)");

    ImGui::InputTextWithHint("##bcon_dbname", "Nazwa bazy danych", DATA::buf_dbname, DATA::buf_dbname.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bcon_user", "Nazwa uzytkownika", DATA::buf_user, DATA::buf_user.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bcon_password", "Haslo", DATA::buf_password, DATA::buf_password.size(), ImGuiInputTextFlags_Password);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    if(ImGui::Button("Sprawdz polaczenie"))
    {
        tryConnect(str.str().c_str());
        DATA::requested_results = true;
    }

    ImGui::SameLine();
    if(DATA::is_conn)
    {
        ImGui::TextColored(sf::Color::Green, "CONNECTION SUCCESSFULL");
    }
    else if(DATA::requested_results)
    {
        ImGui::TextColored(sf::Color::Red, "CONNECTION FAILED: %s", DATA::exception_message.c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formInfo()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "INFORMACJE");
    ImGui::NewLine();
    std::stringstream info1, info2;
    info1 << "Witaj w interfejcie graficznym sluzacym do obslugi bazy danych na uczelni!\n";
    info1 << "Uzywajac panelu po lewej stronie, wyswietl lub dodaj nowe informacje uzywajac formularzy.\n\n";
    info1 << "Program przystosowany jest do obslugi bazy w dowolym miejscu, jako ze istnieje mozliwosc\n";
    info1 << "podania hosta, portu, nazwy bazy danych, loginu uzytkownika oraz hasla. Domyslne wartosci\n";
    info1 << "to 'localhost', '5432', 'u9kluczka', 'u9kluczka'. Zeby wykorzystac gotowa juz baze danych\n";
    info1 << "na serwerze Pascal, nalezy otworzyc tunel ssh na porcie 22 z forwardowaniem portu 5432.\n";
    info1 << "Mozna to osiagnac za pomoca komendy (zamien <nazwisko>):\n\n";

    info2 << "Polaczenie mozesz sprawdzic w zakladce \"Polaczenie\". Gdyby zaistniala taka potrzeba,\n";
    info2 << "rowniez mozna zmienic parametry polaczenia.\n\n";
    info2 << "Do tej informacji zawsze mozesz wrocic, klikajac przycisk \"Informacje\" w panelu.\n\n\n\n";
    info2 << "CZP (Frequently Asked Questions (FAQ), ale po polsku):";

    ImGui::Text("%s", info1.str().c_str());
    ImGui::TextColored(sf::Color::Green, "ssh -L 5432:localhost:5432 9<nazwisko>@pascal.fis.agh.edu.pl -o ServerAliveInterval=180 -o ServerAliveCountMax=2\n\n");
    ImGui::Text("%s", info2.str().c_str());
    auto q = [](const std::string& content) { ImGui::TextColored(sf::Color::Yellow, " - %s", content.c_str()); };
    auto a = [](const std::string& content) { ImGui::Text("%s", content.c_str()); };
    q("Program sie scrashowal, dlaczego?");
    a("Wynika to z faktu, ze \"libpqxx\" jest beznadziejnie napisana biblioteka, ktora uwielbia rzucac");
    a("wyjatki. Zapewniam, ze zrobilem wszystko co w mojej mocy, by takich przypadkow bylo jak najmniej!");
    a("Jednak nie zawsze uda mi sie znalezc wszystkie krytyczne bledy. Niestety o kulawosci biblioteki");
    a("zorientowalem sie za pozno, zeby nie zaprzepaszczac wlozonej juz pracy.\n\n");
    
    q("Baza danych ma wiecej encji, niz ten program ma formularzy.");
    a("Zgadza sie, jesli uzupelniane sa wszystkie pola w formularzach, wiekszosc tabel jest wypelniana");
    a("automatycznie. Urozmaicenie funkcjonalnosci wymagaloby wiecej czasu, ktorego cos ostatnio brakuje.\n\n");

    q("Dlaczego meczysz sie w C++, zamiast jak czlowiek stworzyc interfejs WWW?");
    a("Odpowiedz brzmi: nie wiem, ale sie domyslam.\n\n");

    q("Interfejs jest bardzo \"surowy\", a czcionka nieczytelna.");
    a("Jest to domyslna czcionka biblioteki \"dear imgui\". Jej zmiana wiazalaby sie z utrata prostoty");
    a("dzialania tego programu i kompilacji jego kodu zrodlowego (czy dany system posiada czcionke X?).");
    a("Projekt nie przyznaje (i nie odejmuje?) punktow za jakosc interfejsu graficznego, dlatego tez");
    a("nie poswiecilem temu tyle czasu, ile powinienem.\n\n");

    q("Aplikacja nie ma polskich znakow.");
    a("Patrz: odpowiedz na poprzednie pytanie.\n\n");

    q("Bledy wyswietlaja sie po angielsku.");
    a("Sa to bledy wyrzucane przez biblioteke \"libpqxx\". Oczywiscie moglbym przeslonic ich tresc jakas");
    a("przetlumaczona wiadomoscia, ale wtedy nie otrzymaloby sie wszystkich przydatnych informacji, ktore");
    a("sa wtedy podawane. Lepsze to, niz Microsoftowe \"cos poszlo nie tak\" bez wypisywania kodu bledu ;).");
    
    ImGui::NewLine(); ImGui::TextDisabled("Autor: Aleksander Kluczka");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formInputWydzial()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY WYDZIAL");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_kier_nazwa", "Nazwa", DATA::buf_nazwa, DATA::buf_nazwa.size());
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_kier_skrot", "Skrot nazwy", DATA::buf_skrotnazwy, DATA::buf_skrotnazwy.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(8)");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;
    
    std::stringstream ss;
    ss << "INSERT INTO prj.wydzial (skrot_nazwy, nazwa) values ("
        << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_nazwa.getBuffer(), '\'') << ");";

    auto filled = (DATA::buf_nazwa.length() != 0
        && DATA::buf_skrotnazwy.length() != 0);

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }
    
    if(DATA::query_failed || !DATA::is_conn)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formInputKierunek()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY KIERUNEK");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_kier_nazwa", "Nazwa", DATA::buf_nazwa, DATA::buf_nazwa.size());
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_kier_skrot", "Skrot nazwy", DATA::buf_skrotnazwy, DATA::buf_skrotnazwy.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(8)");

    ImGui::InputTextWithHint("##bin_kier_miejsca", "Liczba miejsc", DATA::buf_miejsca, DATA::buf_miejsca.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_kier_dlugosc", "Dlugosc toku studiow (w semestrach)", DATA::buf_semestr, DATA::buf_semestr.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_kier_stopien", "Stopien", DATA::buf_stopien, DATA::buf_stopien.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_kier_prog", "Prog punktowy", DATA::buf_prog, DATA::buf_prog.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;
    
    std::stringstream ss;
    ss << "INSERT INTO prj.kierunek (skrot_nazwy, nazwa, liczba_miejsc, dlugosc, stopien) values ("
        << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_nazwa.getBuffer(), '\'') << ", "
        << DATA::buf_miejsca.toInt() << ", "
        << DATA::buf_semestr.toInt() << ", "
        << DATA::buf_stopien.toInt() << ");";
    
    if(DATA::buf_prog.length() != 0)
    {
        ss << "INSERT INTO prj.kierunek_wymagania (skrot_nazwy, id_kierunek, prog_punktowy) values ("
            << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << ", "
            << "(SELECT id_kierunek FROM prj.LastKierunek), "
            << DATA::buf_prog.toInt() << ");";
    }

    auto filled = (DATA::buf_nazwa.length() != 0
        && DATA::buf_skrotnazwy.length() != 0
        && DATA::buf_miejsca.length() != 0
        && DATA::buf_semestr.length() != 0
        && DATA::buf_stopien.length() != 0);
    
    // find a faculty where the field with such id does not yet exist
    if(filled)
    {
        std::stringstream query;
        query << "SELECT * FROM prj.WydzialBezKierunku ("
            << std::quoted(DATA::buf_nazwa.getBuffer(), '\'')
            << ");";

        tryConnect(str.str().c_str());
        chooseFromQuery(query.str(), "Przypisz do wydzialu:", 2);
        
        if(DATA::current_choice > 0)
        {
            // need to find ID of an item in a databse, not its position in the result table
            auto ID = (DATA::qresult[DATA::current_choice-1]["id"]).as<int>();
            ss << "INSERT INTO prj.wydzial_kierunek (id_wydzial, id_kierunek, skrot_nazwy) values ("
                << ID << ", "
                << "(SELECT id_kierunek FROM prj.LastKierunek), "
                << std::quoted(DATA::buf_skrotnazwy.getBuffer(), '\'') << ");";
        }
    }

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }

    if(DATA::query_failed || !DATA::is_conn)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formInputProwadzacy()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY PROWADZACY");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_prow_imie", "Imie", DATA::buf_imie, DATA::buf_imie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_prow_drugieimie", "Drugie imie", DATA::buf_drugieimie, DATA::buf_drugieimie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_prow_nazwisko", "Nazwisko", DATA::buf_nazwisko, DATA::buf_nazwisko.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");
    
    ImGui::InputTextWithHint("##bin_prow_email", "Email", DATA::buf_email, DATA::buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;
    
    std::stringstream ss;
    ss << "INSERT INTO prj.prowadzacy (imie, drugie_imie, nazwisko, email) values ("
        << std::quoted(DATA::buf_imie.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_drugieimie.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_nazwisko.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_email.getBuffer(), '\'') << ");";

    // select a free subject from the dropdown list
    tryConnect(str.str().c_str());
    chooseFromQuery("SELECT * FROM prj.PrzedmiotBezProw;", "Wybierz przedmiot:", 1);
    
    if(DATA::current_choice > 0)
    {
        // need to find ID of an item in a databse, not its position in the result table
        auto ID = (DATA::qresult[DATA::current_choice-1]["id_przedmiot"]).as<int>();
        ss << "INSERT INTO prj.prowadzacy_przedmiot (id_przedmiot, id_prowadzacy) values ("
            << ID << ", "
            << "(SELECT id_prowadzacy FROM prj.LastProwadzacy));";
    }
    if(DATA::query_failed || !DATA::is_conn)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }

    // select a faculty from the dropdown list
    chooseFromQuery("SELECT id_wydzial, nazwa, skrot_nazwy FROM prj.wydzial;", "Dostepne wydzialy:", 2, 2, "##submit2");
    
    if(DATA::two.current_choice > 0)
    {
        auto ID = (DATA::two.qresult[DATA::two.current_choice-1]["id_wydzial"]).as<int>();
        ss << "INSERT INTO prj.wydzial_prowadzacy (id_prowadzacy, id_wydzial) values("
            << "(SELECT id_prowadzacy FROM prj.LastProwadzacy), "
            << ID << ");";
    }

    auto filled = (DATA::buf_id != 0)
        && (DATA::buf_imie.length() != 0)
        && (DATA::buf_drugieimie.length() != 0)
        && (DATA::buf_nazwisko.length() != 0)
        && (DATA::buf_email.length() != 0);

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }

    if(DATA::two.query_failed || !DATA::two.is_conn)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formInputPrzedmiot()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY PRZEDMIOT");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_prze_nazwa", "Nazwa", DATA::buf_nazwa, DATA::buf_nazwa.size());
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_prze_semestr", "Numer semestru", DATA::buf_semestr, DATA::buf_semestr.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_prze_ects", "Liczba punktow ECTS", DATA::buf_ects, DATA::buf_ects.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_prze_miejsca", "Liczba miejsc", DATA::buf_miejsca, DATA::buf_miejsca.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::Checkbox("Egzamin", &DATA::buf_egzamin);

    ImGui::InputTextWithHint("##bin_prze_typ", "Typ przedmiotu (obowiazkowy/obieralny)", DATA::buf_typ, DATA::buf_typ.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(16)");

    ImGui::InputTextMultilineWithHint("##bin_prze_opis", "Opis", DATA::buf_opis, DATA::buf_opis.size(), sf::Vector2f(0.f, 300.f));
    ImGui::SameLine(); ImGui::Text("varchar(1024)");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    std::stringstream ss;
    ss << "INSERT INTO prj.przedmiot (nazwa, semestr, liczba_ects, miejsca, egzamin) values ("
        << std::quoted(DATA::buf_nazwa.getBuffer(), '\'') << ", "
        << DATA::buf_semestr.toInt() << ", "
        << DATA::buf_ects.toInt() << ", "
        << DATA::buf_miejsca.toInt() << ", "
        << (DATA::buf_egzamin ? "true" : "false") << ");";

    // if both subject type and description are filled in, insert them to the database
    if((DATA::buf_typ != 0) && (DATA::buf_opis != 0))
    {
        ss << "INSERT INTO prj.przedmiot_informacje (id_przedmiot, typ, opis) values ("
            << "(SELECT id_przedmiot FROM prj.LastPrzedmiot)" << ", "
            << std::quoted(DATA::buf_typ.getBuffer(), '\'') << ", "
            << std::quoted(DATA::buf_opis.getBuffer(), '\'') << ");"; 
    }

    // select a field from the dropdown list
    tryConnect(str.str().c_str());
    chooseFromQuery("SELECT id_kierunek, nazwa, stopien FROM prj.kierunek ORDER BY 1;", "Wybierz kierunek:", 1);

    if(DATA::current_choice > 0)
    {
        auto ID = (DATA::qresult[DATA::current_choice-1]["id_kierunek"]).as<int>();
        ss << "INSERT INTO prj.przedmiot_kierunek (id_kierunek, skrot_nazwy, id_przedmiot) values ("
            << ID << ", "
            << "(SELECT skrot_nazwy FROM prj.kierunek WHERE id_kierunek = " << ID << "), "
            << "(SELECT id_przedmiot FROM prj.LastPrzedmiot)"
            << ");";
    }
    if(DATA::query_failed || !DATA::is_conn)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }

    // select a free professor from the dropdown list
    std::stringstream query;
    query << "SELECT * FROM prj.ProwadzacyBezPrzed;";
    chooseFromQuery(query.str(), "Dostepni prowadzacy:", 2, 2, "##submit2");

    if(DATA::two.current_choice > 0)
    {
        auto ID = (DATA::two.qresult[DATA::two.current_choice-1]["id"]).as<int>();
        ss << "INSERT INTO prj.prowadzacy_przedmiot (id_przedmiot, id_prowadzacy) values("
            << "(SELECT id_przedmiot FROM prj.LastPrzedmiot), "
            << ID << ");";
    }

    auto filled = (DATA::buf_id != 0)
        && (DATA::buf_nazwa.length() != 0)
        && (DATA::buf_semestr.length() != 0)
        && (DATA::buf_ects.length() != 0)
        && (DATA::buf_miejsca.length() != 0);

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }

    if(DATA::two.query_failed || !DATA::two.is_conn)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formInputStudent()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "NOWY STUDENT");
    ImGui::NewLine();    

    auto flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGui::InputTextWithHint("##bin_stud_id", "Numer albumu", DATA::buf_id, DATA::buf_id.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    ImGui::InputTextWithHint("##bin_stud_imie", "Imie", DATA::buf_imie, DATA::buf_imie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_drugieimie", "Drugie imie", DATA::buf_drugieimie, DATA::buf_drugieimie.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_nazwisko", "Nazwisko", DATA::buf_nazwisko, DATA::buf_nazwisko.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_email", "Email", DATA::buf_email, DATA::buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    int step = 1, stepf = 5;
    if(ImGui::InputScalarN("##test4", ImGuiDataType_U32, (void*)DATA::buf_data, 3, &step, &stepf))
    {
        if(DATA::buf_data[0] > 31u) { DATA::buf_data[0] = 31u; }
        else if(DATA::buf_data[0] < 1u) { DATA::buf_data[0] = 1u; }
        if(DATA::buf_data[1] > 12u) { DATA::buf_data[1] = 12u; }
        else if(DATA::buf_data[1] < 1u) { DATA::buf_data[1] = 1u; }
        if(DATA::buf_data[2] > 2022u) { DATA::buf_data[2] = 2022u; }
        else if(DATA::buf_data[2] < 1900u) { DATA::buf_data[2] = 1900u; }
    }
    ImGui::SameLine(); ImGui::Text("date(dd-mm-yyyy)");

    ImGui::InputTextWithHint("##bin_stud_miejscezam", "Miejsce zamieszkania", DATA::buf_miejscezam, DATA::buf_miejscezam.size());
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    ImGui::InputTextWithHint("##bin_stud_plec", "Plec", DATA::buf_plec, DATA::buf_plec.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(16)");

    ImGui::InputTextWithHint("##bin_stud_imieojca", "Imie Ojca", DATA::buf_imieojca, DATA::buf_imieojca.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_imiematki", "Imie Matki", DATA::buf_imiematki, DATA::buf_imiematki.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(32)");

    ImGui::InputTextWithHint("##bin_stud_stopien", "Stopien studiow", DATA::buf_stopien, DATA::buf_stopien.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("int");

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;
    
    std::stringstream query;
    query << "INSERT INTO prj.student (nr_albumu, imie, drugie_imie, nazwisko, email, data_urodzenia) values ("
        << DATA::buf_id.toInt() << ", "
        << std::quoted(DATA::buf_imie.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_drugieimie.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_nazwisko.getBuffer(), '\'') << ", "
        << std::quoted(DATA::buf_email.getBuffer(), '\'') << ", "
        << "TO_DATE('" << DATA::buf_data[0] << "."
            << DATA::buf_data[1] << "."
            << DATA::buf_data[2] << "'"
        << ", 'DD.MM.YYYY'));";
    
    if((DATA::buf_miejscezam != 0)
    || (DATA::buf_plec != 0)
    || (DATA::buf_imieojca != 0)
    || (DATA::buf_imiematki != 0))
    {
        query << "INSERT INTO prj.student_informacje (nr_albumu, miejsce_zamieszkania, plec, imie_ojca, imie_matki) values ("
            << DATA::buf_id.toInt() << ", "
            << std::quoted(DATA::buf_miejscezam.getBuffer(), '\'') << ", "
            << std::quoted(DATA::buf_plec.getBuffer(), '\'') << ", "
            << std::quoted(DATA::buf_imieojca.getBuffer(), '\'') << ", "
            << std::quoted(DATA::buf_imiematki.getBuffer(), '\'') << ");"; 
    }

    if(DATA::buf_stopien.length() != 0)
    {
        tryConnect(str.str().c_str());
        chooseFromQuery("SELECT id_kierunek, nazwa, stopien FROM prj.kierunek WHERE stopien = "+DATA::buf_stopien.toString()+" ORDER BY 1;", "Wybierz kierunek:", 1);
    }

    if(DATA::current_choice > 0)
    {
        auto ID = (DATA::qresult[DATA::current_choice-1]["id_kierunek"]).as<int>();
        query << "INSERT INTO prj.student_kierunek (id_kierunek, skrot_nazwy, nr_albumu, data_rozpoczecia, data_zakonczenia) values ("
            << ID << ", "
            << "(SELECT skrot_nazwy FROM prj.kierunek WHERE id_kierunek = " << ID << "), "
            << DATA::buf_id.toInt() << ", "
            << "(SELECT TO_DATE(CURRENT_TIMESTAMP::VARCHAR, 'YYYY-MM-DD')), "
            << "TO_DATE('2077-5-22', 'YYYY-MM-DD'));";
    }
    // SELECT TO_DATE(CURRENT_TIMESTAMP::VARCHAR, 'YYYY-MM-DD');  // get current date

    auto filled = (DATA::buf_id != 0)
        && (DATA::buf_imie.length() != 0)
        && (DATA::buf_drugieimie.length() != 0)
        && (DATA::buf_nazwisko.length() != 0)
        && (DATA::buf_email.length() != 0);

    if(filled)
    {
        submitButton(str.str(), query.str());
    }
    
    if(DATA::query_failed || !DATA::is_conn)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formOutputAll()
{
    ImGui::Text("Output All");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formOutputKierunek()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA KIERUNKOW");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT * FROM prj.OutKierunek;", {1, 2, 3, 4, 5, 6, 7, 8});
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formOutputProwadzacy()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA PROWADZACYCH");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT * FROM prj.OutProwadzacy;",
        {1, 2, 4, 5, 6, 7});
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formOutputPrzedmiot()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA PRZEDMIOTOW");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT * FROM prj.OutPrzedmiot;",
        {1, 2, 7, 9, 3, 4, 6, 5});
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formOutputStudent()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA STUDENTOW");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT * FROM prj.OutStudent;",
        {1, 4, 2, 5, 6, 8, 12, 10, 11});
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formOutputWydzial()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "LISTA WYDZIALOW");
    ImGui::NewLine();

    std::stringstream str;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    tableFromQuery("SELECT * FROM prj.OutWydzial;",
        {1, 2, 3, 4, 5});
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void formRegisterStudentPrzedmiot()
{
    ImGui::TextColored(sf::Color{230, 230, 140}, "REJESTRACJA NA PRZEDMIOTY OBIERALNE");
    ImGui::NewLine();

    auto flags = ImGuiInputTextFlags_CharsNoBlank;

    ImGui::InputTextWithHint("##breg_stpr_nazwisko", "Numer albumu", DATA::buf_id, DATA::buf_id.size(), flags | ImGuiInputTextFlags_CharsDecimal);
    ImGui::SameLine(); ImGui::Text("varchar(8)");

    ImGui::InputTextWithHint("##breg_stpr_email", "Email", DATA::buf_email, DATA::buf_email.size(), flags);
    ImGui::SameLine(); ImGui::Text("varchar(64)");

    std::stringstream str, ss;
    str << "host=" << DATA::buf_host
        << " dbname=" << DATA::buf_dbname
        << " user=" << DATA::buf_user
        << " port=" << DATA::buf_port
        << " password=" << DATA::buf_password;

    tryConnect(str.str().c_str());
    chooseFromQuery("SELECT id, nazwa, egzamin FROM prj.OutPrzedObieralne;", "Wybierz przedmiot obieralny:", 1);

    if(DATA::current_choice > 0)
    {
        // need to find ID of an item in a databse, not its position in the result table
        auto ID = (DATA::qresult[DATA::current_choice-1]["id"]).as<int>();
        ss << "INSERT INTO prj.student_przedmiot (id_przedmiot, nr_albumu, srednia_ocen) values ("
            << ID << ", "
            << DATA::buf_id.toInt() << ", "
            << 0 << ");";
    }

    auto filled = (DATA::buf_id != 0)
        && (DATA::buf_email.length() != 0)
        && (DATA::current_choice > 0);

    if(filled)
    {
        submitButton(str.str(), ss.str());
    }
    
    if(DATA::query_failed || !DATA::is_conn)
    {
        ImGui::TextColored(sf::Color::Red, "%s", DATA::exception_message.c_str());
    }
}
