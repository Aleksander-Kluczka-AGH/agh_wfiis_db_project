#include "include/Application.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv)
{
    Application app("Aleksander Kluczka - Bazy Danych 1 - Projekt", sf::Vector2f(1280.f, 720.f), 30u);
    app.run();
    return 0;
}