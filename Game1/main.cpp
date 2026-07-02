#include <SFML/Graphics.hpp>

int main()
{
    // create a window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Pong");

    // Paddle
    sf::RectangleShape paddle({ 100.f, 20.f });
    paddle.setPosition({ 350.f, 560.f });
    paddle.setFillColor(sf::Color::White);

    // ball
    sf::CircleShape ball( 10.f );
    paddle.setPosition({ 390.f, 290.f });
    paddle.setFillColor(sf::Color::White);

    // Game Loop
    while (window.isOpen())
    {
		// Timer for starting the ball
        sf::Clock timer;
        bool ballStarted = false;
        float ballSpeed = 4.f;

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

		// Paddle movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            paddle.move({ -0.5f, 0.f });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            paddle.move({ 0.5f, 0.f });
        }

		// Start the ball after 5 seconds
        if (!ballStarted && timer.getElapsedTime().asSeconds() >= 0.5f)
        {
            ballStarted = true;
        }

        if (ballStarted)
        {
            ball.move({ 0.f, ballSpeed });
        }

        window.clear(sf::Color::Black);

        // Draw objects here
        window.draw(ball);
		window.draw(paddle);

        window.display();
    }
    return 0;
}