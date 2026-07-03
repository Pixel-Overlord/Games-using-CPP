#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Class that acts as main game engine.It handles the game loop, updates, and rendering.

class Game
{
private: 
	// private functions
	void initVariables();
	void initWindow();

public:
	// Constructors and Destructors
	Game();
	virtual ~Game();	// destructor

	// Functions
	void update();
	void render();
};

