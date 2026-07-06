#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Class that acts as main game engine.It handles the game loop, updates, and rendering.

class Game
{
private: 
	// Variables for Window
	sf::RenderWindow* window;	// dynamically allocated window object
	sf::VideoMode videoMode;	
	sf::Event ev;

	// Mouse Positions
	sf::Vector2i mousePosWindow;	// relative to the window
	sf::Vector2f mousePosView;		// relative to the view

	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Game Logic Variables
	unsigned points;
	int health;
	bool endGame;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// Vector to hold multiple enemies
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();

public:
	// Constructors and Destructors
	Game();
	virtual ~Game();	// destructor

	// Accessors
	const bool running() const;	// check if the window is running or open.
	const bool getEndGame() const;	// check if the game has ended.

	// Functions
	void pollEvents();	// handle events
	void spawnEnemy();
	void updateMousePositions();

	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};