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
	// Variables
	// Window
	sf::RenderWindow* window;	// dynamically allocated window object
	sf::VideoMode videoMode;	
	sf::Event ev;

	// private functions
	void initVariables();
	void initWindow();

public:
	// Constructors and Destructors
	Game();
	virtual ~Game();	// destructor

	// Accessors
	const bool running() const;	// check if the window is open

	// Functions
	void pollEvents();	// handle events
	void update();
	void render();
};

