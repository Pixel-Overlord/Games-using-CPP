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
}

// Constructors
Game::Game()
{
	// Initialize member variables and create the game window
	this->initVariables();
	this->initWindow();
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

	this->window->clear(sf::Color(255, 0, 0, 255));	// clear the window with color

	// Draw game here
	this->window->display();	// window is ready to display added objects (or rendered frame)
}