#pragma once

#include "Root.hpp"
#include "Section.hpp"
#include "Forms.hpp"
#include "DataManager.hpp"

class Application final
{
    public:
    Application(const std::string_view &title, const sf::Vector2f& size, const unsigned int& frame_limit);
    ~Application();
    void run();

    private:
    void placeMenuSection();
    void placeFormSection();
    void update();
    void render();

    public:
    sf::Vector2f size;

    private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Event m_event;

    int m_activeSection;

    enum ActiveSection
    {
        Info = 0,
        Connection,

        Input_Przedmiot,
        Input_Prowadzacy,
        Input_Student,

        Register_StudentPrzedmiot,
        
        Output_All,
        Output_Przedmiot,
        Output_Prowadzacy,
        Output_Student,
        Output_Kierunek
    };
};