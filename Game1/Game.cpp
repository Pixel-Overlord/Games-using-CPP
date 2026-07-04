#include "Game.h"

// Private functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Pong", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	this-> window->setFramerateLimit(144);
}

void Game::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(400.f, 300.f));

	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));	// scale the enemy to half its original size

	this->enemy.setFillColor(sf::Color::Cyan);

	this->enemy.setOutlineThickness(1.f);
	this->enemy.setOutlineColor(sf::Color::Cyan);
}

// Constructors
Game::Game()
{
	// Initialize member variables and create the game window
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

// Destructors
Game::~Game()
{
	delete this->window;	// release memory allocated for the window object
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();	
}

void Game::pollEvents()
{
	// Event Polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

// Functions
void Game::update()
{
	this->pollEvents();	// handle events

	//// update mouse position relative to the screen
	//std::cout << "Mouse Position relative to the screen: " << sf::Mouse::getPosition().x << ", " << sf::Mouse::getPosition().y << std::endl;

	//// update mouse position relative to the window
	//std::cout << "Mouse Position Relative to Window: " << sf::Mouse::getPosition(*this->window).x << ", " << sf::Mouse::getPosition(*this->window).y << std::endl;
}

void Game::render()
{
	/*
	* Renderes the game objects on the screen. This function is called once per frame.
	*
	*  - clears the old frame
	*  - render objects
	*  - draws the new frame
	*/

	this->window->clear(sf::Color::Black);	// clear the window with color
	// Draw game here

	this->window->draw(this->enemy);

	this->window->display();	// window is ready to display added objects (or rendered frame)
}