#include "../include/Section.hpp"

Section::Section(const std::string_view& title,
    const sf::Vector2f& pos,
    const sf::Vector2f& size,
    const ImGuiWindowFlags& flags)
:m_flag(true)
{
    m_flag = m_flag && ImGui::Begin(title.compare("") ? title.data() : "default-title", nullptr, flags);

    ImGui::SetWindowSize(size);
    ImGui::SetWindowPos(pos);
}

Section::~Section()
{
    ImGui::End();
    m_flag = false;
}

Section::operator bool() const
{
    return m_flag;
}