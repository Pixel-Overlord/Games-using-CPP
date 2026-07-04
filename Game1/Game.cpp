#include "Game.h"

// Private functions
void Game::initVariables()
{
	this->window = nullptr;

	// Game logic variables
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Pong", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	this-> window->setFramerateLimit(60);
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
/*
 * @ return void
 * 
 * Spawns a new enemy and adds it to the enemies vector.
 *	- sets a random color
 *	- sets a random posiiton.
 *	- add enemy to enemies vector
*/
void Game::spawnEnemy()
{
	// random x position within the window width
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color(
		rand() % 256,	// random red value
		rand() % 256,	// random green value
		rand() % 256	// random blue value
	));

	this->enemies.push_back(this->enemy);	// add the enemy to the vector
}

/*
 * @ return void
 * 
 * Updates the mouse positions:
 * 	-relative to the window (Vector2i)
*/
void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);	// get mouse position relative to the window
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);	// get mouse position relative to the view
}

/*
 * @ return void
 * 
 * Updates the enemy spawn timer and spawns new enemies
 * when the total number of enemies is smaller than the maximum.
 * 
 * Moves the enemies down the screen.
 * 
 * Removes enemies from the vector when they are destroyed or go off the screen.
*/
void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// spawn an enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	/*
	* Move the enemies down the screen and remove them if they are clicked on or go off the screen	
	*/
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleteEnemy = false;

		this->enemies[i].move(0.f, 3.f);

		// Remove enemies that are clicked on by the mouse
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// check if the mouse position is within the bounds of the enemy
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleteEnemy = true;

				// Gain points
				this->points += 1;
			}
		}

		// Remove enemies that go off the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleteEnemy = true;
		}

		if (deleteEnemy)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::update()
{
	this->pollEvents();	// handle events

	this->updateMousePositions();

	this->updateEnemies();
}

void Game::renderEnemies()
{
	// Render the enemies on the screen
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

/*
* Renderes the game objects on the screen. This function is called once per frame.
*
*  - clears the old frame with a color
*  - render objects
*  - draws the new frame
* 
* Note : The order of rendering matters, 
		 objects rendered later will be on top of objects rendered earlier.
*/
void Game::render()
{
	this->window->clear(sf::Color::Black);

	// Draw game here
	this->renderEnemies();

	this->window->display();	// window is ready to display added objects (or rendered frame)
}