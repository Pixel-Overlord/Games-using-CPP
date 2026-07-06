#pragma once

#include <iostream>
#include <vector>
#include <ctime>

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

	void updateEnemies();
	void update();

	void renderEnemies();
	void render();
};