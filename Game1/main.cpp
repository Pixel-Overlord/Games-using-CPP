#include <iostream>
#include "Game.h"

int main()
{
    // Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong", sf::Style::Titlebar| sf::Style::Close| sf::Style::Resize);

    sf::Event ev;

    // Font
    sf::Font font;
    font.loadFromFile("D:/Games - C++/Game Repos/Game1/Game1/Fonts/game_over.ttf");

    // Timer
    sf::Clock timer;
    bool ballStarted = false;

    // Game Loop
    while (window.isOpen())
    {
		// Event Polling
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
			    case sf::Event::Closed :
                    window.close();
			    	break;

				case sf::Event::KeyPressed:
                    if (ev.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                    break;

                default:
					break;
            }
        }

		// Rendering
		window.clear(sf::Color::Black); // Clear old frame

		// Draw your game objects here

		window.display();   // Tell app that the window is done drawing and to display the new frame
    }

    return 0;
}