#include "game.hpp"
#include "util.hpp"
#include "input.hpp"
#include "life.hpp"
#include "fontobject.hpp"
#include "segment.hpp"
#include "time.hpp"
#include "player.hpp"
#include "npc.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace GameMap
{
	const int MAP_WIDTH = 3000;
	const int MAP_HEIGHT = 3000;

	const int MIN_PREY = 40;
	const int MAX_PREY = 100;

	const int MIN_PREDATOR = 1;
	const int MAX_PREDATOR = 4;

	const int MIN_FOOD = 100;
	const int MAX_FOOD = 100;
	const float FOOD_DENSITY = 0.00001f;
}

Game::Game()
{}

Game::~Game()
{}

bool Game::init(bool fullscreen)
{
	this->_graphics = Graphics::getInstance();

	this->_globals.setGameMapWidth(GameMap::MAP_WIDTH);
	this->_globals.setGameMapHeigth(GameMap::MAP_HEIGHT);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() < 0)
	{
		Util::logError("Initalizing failure", "SDL Subsystems failed to initialize properly", SDL_GetError());
		return false;
	}

	if (fullscreen)
	{
		this->_graphics->setWindowMode(Util::getGameName());
		Util::setFullscreenMode(*this->_graphics);
		this->_globals.setScreenWidth(Util::getScreenWidth());
		this->_globals.setScreenHeight(Util::getScreenHeight());
	}
	else
	{
		this->_graphics->setWindowMode(Util::getGameName(), false, Util::getScreenWidth(), Util::getScreenHeight());
	}

	this->_graphics->setRenderColor(Color::white());

	/* Custom class initialization */

	// Setting up player
	_player = Player("assets/playerCircle.png", 20.0f);
	_player.setPosition(Point(200,100));

	// Setting up food
	this->_foodManager.setEntityDensity(GameMap::FOOD_DENSITY);
	this->_foodManager.setLowerEntityBound(GameMap::MIN_FOOD);
	this->_foodManager.setUpperEntityBound(GameMap::MAX_FOOD);
	this->_foodManager.populate();

	// Setting up prey
	this->_preyManager.setLowerEntityBound(GameMap::MIN_PREY);
	this->_preyManager.setUpperEntityBound(GameMap::MAX_PREY);
	this->_preyManager.populate();

	// Setting up predators
	this->_predatorManager.setLowerEntityBound(GameMap::MIN_PREDATOR);
	this->_predatorManager.setLowerEntityBound(GameMap::MAX_PREDATOR);
	this->_predatorManager.populate();

	// Setting up map borders
	this->_boundingBox = {
		Segment(Point(0, 0), Point(0, GameMap::MAP_HEIGHT)),
		Segment(Point(GameMap::MAP_WIDTH, GameMap::MAP_HEIGHT), Point(0, GameMap::MAP_HEIGHT)),
		Segment(Point(GameMap::MAP_WIDTH, GameMap::MAP_HEIGHT), Point(GameMap::MAP_WIDTH, 0)),
		Segment(Point(0, 0), Point(GameMap::MAP_WIDTH, 0))
	};

	// Setting up all collisions
	this->collisionObjects.push_back(&this->_player.getCircle());

	for (auto &seg : this->_boundingBox)
	{
		this->collisionObjects.push_back(&seg);
	}

	this->_nourishmentDisplay = FontObject(200, 30);
	this->_nourishmentDisplay.setPosition(Point(Util::getScreenWidth() / 2 - 200 / 2, 10));
	this->_nourishmentDisplay.setColor(Color::grey());
	
	/* End of class initialization */

	this->_isRunning = true;
	return true;
}

void Game::handleUserInput()
{
	this->_input.beginNewFrame();

	if (SDL_PollEvent(&this->_event))
	{
		if (this->_event.type == SDL_QUIT)
		{
			exit();
		}
		else if (this->_event.type == SDL_KEYDOWN)
		{
			if (this->_event.key.repeat == 0)
				this->_input.keyDownEvent(this->_event);
		}
		else if (this->_event.type == SDL_KEYUP)
		{
			this->_input.keyUpEvent(this->_event);
		}
	}

	// Custom key handling
	
	if (this->_input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		exit();
	}

	if(this->_input.wasKeyPressed(SDL_SCANCODE_R))
	{
		this->_graphics->setStandardColor(Color(Util::randInt(150, 255), Util::randInt(150, 255), Util::randInt(150, 255), 255));
	}

	if(this->_input.isKeyHeld(SDL_SCANCODE_W)) { this->_player.move(Util::Direction::TOP); }
	if (this->_input.isKeyHeld(SDL_SCANCODE_A)) { this->_player.move(Util::Direction::LEFT); }
	if (this->_input.isKeyHeld(SDL_SCANCODE_S)) { this->_player.move(Util::Direction::BOTTOM); }
	if (this->_input.isKeyHeld(SDL_SCANCODE_D)) { this->_player.move(Util::Direction::RIGHT); }

	// End of custom key handling
}

void Game::update()
{
	/* UPDATING */

	this->_player.update();

	this->_predatorManager.findFood(this->_preyManager.getEntities());
	this->_predatorManager.findFood(&this->_player);
	this->_predatorManager.update();

	this->_preyManager.eatCheck(this->_predatorManager.getEntities());
	this->_preyManager.findFood(this->_foodManager.getEntities());
	this->_preyManager.update();

	this->_foodManager.eatCheck(this->_preyManager.getEntities());
	this->_foodManager.eatCheck(&this->_player);
	this->_foodManager.update();

	/* COLLISIONS */

	this->_player.collide(this->collisionObjects);

	this->_preyManager.collide(this->collisionObjects);
	this->_preyManager.collide(this->_preyManager.getCollisionObjects());

	this->_foodManager.collide(this->collisionObjects);
	this->_foodManager.collide(this->_foodManager.getCollisionObjects());

	this->_predatorManager.collide(this->collisionObjects);
	this->_predatorManager.collide(this->_foodManager.getCollisionObjects());
}

void Game::render()
{
	this->_graphics->fillBackground();

	/* Rendering of custom classes */

	// Position shift as the world is rendered in function of player position
	Point shift = this->_player.getCircle().getFixedShift();

	for(int i = 0; i < _boundingBox.size(); i++)
	{
		_boundingBox[i].draw(*this->_graphics, shift);
	}

	this->_player.draw();
	this->_foodManager.draw(shift);
	this->_preyManager.draw(shift);
	this->_predatorManager.draw(shift);

	this->_nourishmentDisplay.update(*this->_graphics, "NOURISHMENT: " + std::to_string(this->_player.getNourishment()));
	this->_nourishmentDisplay.draw(*this->_graphics);

	/* End of custom rendering */

	this->_graphics->flip();
}

void Game::exit()
{
	this->_isRunning = false;
	this->_graphics->~Graphics();
	SDL_Quit();
}

bool Game::running()
{
	return _isRunning;
}

void Game::run()
{
	unsigned int last = SDL_GetTicks();
	unsigned int timeElapsed;

	while (this->running())
	{
		this->handleUserInput();

		if (!this->running())
		{
			return;
		}

		this->update();
	
		timeElapsed = SDL_GetTicks() - last;

		if (timeElapsed >= (1000 / _framerate))
		{
			this->render();
			last = SDL_GetTicks();
		}

		SDL_Delay(10);
	}
}

// Getters and Setters

void Game::setFramerate(int framerate)
{
	this->_framerate = framerate;
}

void Game::setVerbose(bool verbose)
{
	this->_verbose = verbose;
}

void Game::setScreenSize(int width, int height)
{
	Util::setWindowedMode(width, height);
}