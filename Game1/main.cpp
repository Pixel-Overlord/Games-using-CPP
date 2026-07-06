#include <iostream>
#include "Game.h"

int main()
{
	// Seed the random number generator
	std::srand(static_cast<unsigned>(time(NULL)));

	// Init new game object
	Game game;

    // Timer
    sf::Clock timer;
    bool ballStarted = false;

    // Game Loop
    while (game.running() && !game.getEndGame())
    {
		// update
		game.update();

		// render
		game.render();
    }

    return 0;
}