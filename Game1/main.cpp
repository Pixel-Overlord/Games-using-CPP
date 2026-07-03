#include <iostream>
#include "Game.h"

int main()
{
	// Init new game object
	Game game;

    // Font
    sf::Font font;
    font.loadFromFile("D:/Games - C++/Game Repos/Game1/Game1/Fonts/game_over.ttf");

    // Timer
    sf::Clock timer;
    bool ballStarted = false;

    // Game Loop
    while (game.running())
    {
		// update
		game.update();

		// render
		game.render();
    }

    return 0;
}