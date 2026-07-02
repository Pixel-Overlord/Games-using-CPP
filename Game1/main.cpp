#include <SFML/Graphics.hpp>

int main()
{
    // create a window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Pong");

    // Game Loop
    while (window.isOpen())
    {
        // Event loop
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Blue);

        // Draw objects here
        window.display();
    }
    return 0;
}