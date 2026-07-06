#include "Game.h"

// Private functions
void Game::initVariables()
{
	this->window = nullptr;

	// Game logic variables
	this->points = 0;
	this->health = 30;
	this->endGame = false;
	this->enemySpawnTimerMax = 15.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->paused = false;
}

void Game::initWindow()
{
	this->videoMode.height = 1000;
	this->videoMode.width = 500;

	this->window = new sf::RenderWindow(this->videoMode, "Pong", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	this-> window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/zrnic-rg.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}

	if (this->gameOverFont.loadFromFile("Fonts/Pixel-Game.otf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
	// set the position of the text to the top left corner of the window
	this->uiText.setPosition(10.f, 10.f);

	this->pauseText.setFont(this->font);
	this->pauseText.setCharacterSize(60);
	this->pauseText.setFillColor(sf::Color::Yellow);
	this->pauseText.setString("PAUSED");
	this->pauseText.setPosition(180.f, 450.f);

	this->gameOverText.setFont(this->gameOverFont);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER");
	this->gameOverText.setPosition(100.f, 450.f);
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
	this->initFonts();
	this->initText();
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

const bool Game::getEndGame() const
{
	return this->endGame;
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

			if (this->ev.key.code == sf::Keyboard::Space)
			{
				this->paused = !this->paused;
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
 *  - sets a random difficulty (size) of the enemy.
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

	// Randomize enemy type. The higher the number, the easier the enemy.
	int type = rand() % 5;

	switch (type)
	{
		case 0:
			this->enemy.setSize(sf::Vector2f(30.f, 30.f));
			this->enemy.setFillColor(sf::Color::Magenta);
			break;
		case 1:
			this->enemy.setSize(sf::Vector2f(50.f, 50.f));
			this->enemy.setFillColor(sf::Color::Blue);
			break;
		case 2:
			this->enemy.setSize(sf::Vector2f(65.f, 65.f));
			this->enemy.setFillColor(sf::Color::Cyan);
			break;
		case 3:
			this->enemy.setSize(sf::Vector2f(80.f, 80.f));
			this->enemy.setFillColor(sf::Color::Red);
			break;
		case 4:	
			this->enemy.setSize(sf::Vector2f(100.f, 100.f));
			this->enemy.setFillColor(sf::Color::Green);
			break;
		default:
			this->enemy.setSize(sf::Vector2f(30.f, 30.f));
			this->enemy.setFillColor(sf::Color::White);
			break;
	}

	this->enemies.push_back(this->enemy);	// add the enemy to the vector
}

/*
 * @ return void
 * 
 * Updates the mouse positions:
 * 	- relative to the window (Vector2i)
*/
void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);	// get mouse position relative to the window
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);	// get mouse position relative to the view
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health;

	this->uiText.setString(ss.str());
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
	* Move and update the enemies.
	*/
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleteEnemy = false;

		this->enemies[i].move(0.f, 3.f);

		// Highlight the enemy when the mouse is over it
		if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
		{
			this->enemies[i].setScale(0.9f, 0.9f);
			this->enemies[i].setOutlineThickness(3.f);
			this->enemies[i].setOutlineColor(sf::Color::White);
		}
		else
		{
			this->enemies[i].setScale(1.f, 1.f);
			this->enemies[i].setOutlineThickness(1.f);
			this->enemies[i].setOutlineColor(this->enemies[i].getFillColor());
		}

		// Remove enemies that go off the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);

			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
		}
	}

	// Remove enemies that are clicked on by the mouse
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleteEnemy = false;
			for (int i = 0; i < this->enemies.size() && deleteEnemy == false; i++)
			{
				// check if the mouse position is within the bounds of the enemy
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					// Gain points
					if (this->enemies[i].getFillColor() == sf::Color::Magenta) {
						points += 10;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Blue) {
						points += 7;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan) {
						points += 5;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Red) {
						points += 3;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Green) {
						points += 1;
					}

					std::cout << "Points: " << this->points << "\n";

					// delete the enemy
					deleteEnemy = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}

	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	this->pollEvents();	// handle events

	if (this->paused)
		return;

	if (!this->endGame)
	{
		this->updateMousePositions();
		this->updateText();
		this->updateEnemies();
	}


	// Endgame condition
	if (this->health <= 0 && !this->endGame)
	{
		this->updateText();

		this->endGame = true;
		std::cout << "Game Over! Final Score: " << this->points << "\n";
		this->gameOverClock.restart();
	}

	/* The flow is:
	 *	- Health reaches 0.
	 *	- endGame becomes true.
	 *	- "GAME OVER" is drawn every frame.
	 *	- After 3 seconds, the window closes.
	*/
	if (this->endGame)
	{
		if (this->gameOverClock.getElapsedTime().asSeconds() >= 3.f)
		{
			this->window->close();
		}

		return;
	}
}

/*
 * Renders the text not only on the window but also on the target (which can be a window or a texture).
*/
void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	// Render the enemies on the screen
	for (auto& e : this->enemies)
	{
		target.draw(e);
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
	this->renderEnemies(*this->window);
	this->renderText(*this->window);

	// Draw the pause text if the game is paused
	if (this->paused)
	{
		this->window->draw(this->pauseText);
	}

	// Draw the game over text if the game has ended
	if (this->endGame)
	{
		this->window->draw(this->gameOverText);
	}

	this->window->display();	// window is ready to display added objects (or rendered frame)
}