#pragma once

#include "Root.hpp"

class Section
{
    public:
    Section(const std::string_view& title,
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        const ImGuiWindowFlags& flags =
            ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoTitleBar);
    ~Section();

    operator bool() const;

    private:
    bool m_flag;
};