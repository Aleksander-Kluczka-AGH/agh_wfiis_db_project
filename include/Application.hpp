#pragma once

#include "Section.hpp"
#include "Forms.hpp"

/**
 * @brief The main application interface
 */
class Application final
{
    public:
    /**
     * @brief Constructor
     * 
     * @param title The title of the application visible as window title
     * @param size The size of the window
     * @param frame_limit The frame-per-second limit
     */
    Application(const std::string_view &title, const sf::Vector2f& size, const unsigned int& frame_limit);

    /**
     * @brief Default destructor
     */
    ~Application();

    /**
     * @brief Call this member function to start the application
     */
    void run();

    private:
    /**
     * @brief Places Menu subwindow in the application
     */
    void placeMenuSection();

    /**
     * @brief Places Form subwindow in the application
     */
    void placeFormSection();

    /**
     * @brief Updates SFML and ImGui events, processes app logic
     */
    void update();

    /**
     * @brief Renders SFML and ImGui content to the window
     */
    void render();

    public:
    sf::Vector2f size; // The size of the window

    private:
    sf::RenderWindow m_window; // The window target for rendering
    sf::Clock m_clock; // The clock object handling window refresh
    sf::Event m_event; // The event handler

    int m_activeSection; // Flag representing currently active section of the app

    /**
     * @brief The enum listing all application sections
     */
    enum ActiveSection
    {
        Info = 0,
        Connection,

        Input_Przedmiot,
        Input_Prowadzacy,
        Input_Student,
        Input_Kierunek,
        Input_Wydzial,

        Register_StudentPrzedmiot,
        
        Output_All,
        Output_Przedmiot,
        Output_Prowadzacy,
        Output_Student,
        Output_Kierunek,
        Output_Wydzial
    };
};
