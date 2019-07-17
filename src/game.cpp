#include "game.hpp"
#include "util.hpp"
#include "input.hpp"
#include "life.hpp"
#include "segment.hpp"
#include "time.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// =============== DEBUG ONLY =================

#include <iostream>

// ============================================

namespace GameMap
{
	const int MAP_WIDTH = 1200;
	const int MAP_HEIGHT = 1200;
	const int MIN_NPC = 10;
	const int MAX_NPC = 100;
	const int SPAWN_BORDER_DISTANCE = 40;
}

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init(bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Util::logError("Initalizing failure", "SDL Subsystems failed to initialize properly", SDL_GetError());
		return false;
	}

	if (this->_verbose)
	{
		Util::logInfo("SDL Subsystems initialized");
	}

	if (fullscreen)
	{
		this->_graphics = new Graphics(Util::getGameName());
	}
	else
	{
		this->_graphics = new Graphics(Util::getGameName(), false, Util::getScreenWidth(), Util::getScreenHeight());
	}
	
	this->_graphics->setRenderColor(Color::white());

	/* Custom class initialization */

	// Set up player
	this->_player = new Life();
	this->_player->loadSprite(*this->_graphics, "assets/square.png", 310, 310, 0.1);
	this->_player->setCentered(true);
	this->_player->setPosition(
		Point(Util::randInt(GameMap::SPAWN_BORDER_DISTANCE, GameMap::MAP_WIDTH - GameMap::SPAWN_BORDER_DISTANCE), 
					Util::randInt(GameMap::SPAWN_BORDER_DISTANCE, GameMap::MAP_HEIGHT - GameMap::SPAWN_BORDER_DISTANCE)));

	// Set up npcs
	for(int i = 0; i < Util::randInt(GameMap::MIN_NPC, GameMap::MAX_NPC); i++)
	{
		this->_npcs.push_back(Life());
		this->_npcs.back().loadSprite(*this->_graphics, "assets/squarenpc.png", 512, 512, (310.0 * 0.1) / 512.0);
		this->_npcs.back().setPosition(
			Point(Util::randInt(GameMap::SPAWN_BORDER_DISTANCE, GameMap::MAP_WIDTH - GameMap::SPAWN_BORDER_DISTANCE), 
						Util::randInt(GameMap::SPAWN_BORDER_DISTANCE, GameMap::MAP_HEIGHT - GameMap::SPAWN_BORDER_DISTANCE)));
	}

	_ticksLastNpcMove = SDL_GetTicks();

	// Set up map borders
	this->boundingBox = {
	Segment(Point(0, 0), Point(0, GameMap::MAP_HEIGHT)),
	Segment(Point(GameMap::MAP_WIDTH, GameMap::MAP_HEIGHT), Point(0, GameMap::MAP_HEIGHT)),
	Segment(Point(GameMap::MAP_WIDTH, GameMap::MAP_HEIGHT), Point(GameMap::MAP_WIDTH, 0)),
	Segment(Point(0, 0), Point(GameMap::MAP_WIDTH, 0))};

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

	if (this->_input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		exit();
	}

	// Custom key handling

	if(this->_input.wasKeyPressed(SDL_SCANCODE_R))
	{
		this->_backgroundColor = Color(Util::randInt(150, 255), Util::randInt(150, 255), Util::randInt(150, 255), 255);
	}

	if(this->_input.isKeyHeld(SDL_SCANCODE_W))
	{
		this->_player->moveUp();
	}
	
	if (this->_input.isKeyHeld(SDL_SCANCODE_A))
	{
		this->_player->moveLeft();
	}

	if (this->_input.isKeyHeld(SDL_SCANCODE_S))
	{
		this->_player->moveDown();
	}

	if (this->_input.isKeyHeld(SDL_SCANCODE_D))
	{
		this->_player->moveRight();
	}

	// End of custom key handling
}

void Game::update()
{
	/* Updating of game classes */

	if(SDL_GetTicks() - _ticksLastNpcMove > 150)
	{
		for(auto &npc : this->_npcs)
		{
			npc.setRandomMovement();
		}
		_ticksLastNpcMove = SDL_GetTicks();
	}

	std::vector<Life *> lives;

	for (auto &npc : this->_npcs)
	{
		npc.update();
		lives.push_back(&npc);
	}

	lives.push_back(_player);

	this->_player->update();
	this->_player->collisionCheck(boundingBox, lives);

	for(auto &npc : this->_npcs)
	{
		npc.collisionCheck(boundingBox, lives);
	}

	/* End of updating */
}

void Game::render()
{
	_graphics->setRenderColor(this->_backgroundColor);
	_graphics->fillBackground();

	/* Rendering of different classes */

	this->_player->draw(*this->_graphics);

	const Point shift = this->_player->getCenteredShift();

	for(auto &npc : this->_npcs)
	{
		npc.draw(*this->_graphics, shift);
	}

	_graphics->setRenderColor(this->_segmentColor);
	for(int i = 0; i < boundingBox.size(); i++)
	{
		boundingBox[i].draw(*this->_graphics, shift);
	}

	/* End of rendering */

	_graphics->flip();
}

void Game::exit()
{
	_isRunning = false;
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
		timeElapsed = SDL_GetTicks() - last;

		this->handleUserInput();
		this->update();

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
