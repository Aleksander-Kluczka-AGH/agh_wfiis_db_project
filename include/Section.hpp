#pragma once

#include "Root.hpp"

/**
 * @brief The section of the application interface
 */
class Section
{
    public:
    /**
     * @brief Constructor of the Section object
     * 
     * @param title The title of the @c Section
     * @param pos The position of the @c Section relative to the window
     * @param size The size of the @c Section
     * @param flags Flags passed to ImGui handler
     */
    Section(const std::string_view& title,
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        const ImGuiWindowFlags& flags =
            ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoTitleBar);

    /**
     * @brief Default constructor
     */
    ~Section();

    /**
     * @brief Implicit cool conversion operator
     * 
     * @return True if the object exists, false if it is soon to be destroyed
     */
    operator bool() const;

    private:
    bool m_flag; /**< Is the Section going to be destroyed? */
};