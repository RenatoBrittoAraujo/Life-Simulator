#include "game.hpp"
#include "util.hpp"
#include "input.hpp"
#include "life.hpp"
#include "segment.hpp"
#include "time.hpp"
#include "player.hpp"
#include "npc.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// =============== DEBUG ONLY =================

#include <iostream>

// ============================================

namespace GameMap
{
	const int MAP_WIDTH = 1200;
	const int MAP_HEIGHT = 1200;
	const int MIN_NPC = 20;
	const int MAX_NPC = 80;
	const int SPAWN_BORDER_DISTANCE = 40;
}

Game::Game()
{}

Game::~Game()
{}

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

	// Setting up player
	_player = Player(*this->_graphics, "playerSquare.png", 50.0f, 50.0f);
	_player.getBox().setPosition(Point(200,100));

	// Setting up NPCs
	for(int i = 0; i < Util::randInt(GameMap::MIN_NPC, GameMap::MAX_NPC); i++)
	{
		NPC npc = NPC(*this->_graphics, "npcSquare.png", 40.0f, 40.0f);
		npc.getBox().setPosition(Point(Util::randInt(50, GameMap::MAP_WIDTH - 50), Util::randInt(50, GameMap::MAP_HEIGHT)));
		this->_npcs.push_back(npc);
	}

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
		this->_graphics->setStandardColor(Color(Util::randInt(150, 255), Util::randInt(150, 255), Util::randInt(150, 255), 255));
	}

	if(this->_input.isKeyHeld(SDL_SCANCODE_W))
	{
		this->_player.getBox().move(Util::Direction::TOP);
	}
	
	if (this->_input.isKeyHeld(SDL_SCANCODE_A))
	{
		this->_player.getBox().move(Util::Direction::LEFT);
	}

	if (this->_input.isKeyHeld(SDL_SCANCODE_S))
	{
		this->_player.getBox().move(Util::Direction::BOTTOM);
	}

	if (this->_input.isKeyHeld(SDL_SCANCODE_D))
	{
		this->_player.getBox().move(Util::Direction::RIGHT);
	}

	// End of custom key handling
}

void Game::update()
{
	/* Updating of game classes */

	this->_player.update();

	for(auto& npc : this->_npcs)
	{
		npc.update();
	}

	/* Collisions */

	if(SDL_GetTicks() - _ticksLastNpcMove > 150)
	{
		for (auto &npc : this->_npcs)
		{
			npc.changeMovement();
		}
		_ticksLastNpcMove = SDL_GetTicks();
	}

	std::vector<GameObject*> gameObjects;

	gameObjects.push_back(&this->_player.getBox());

	for(auto &seg : this->boundingBox)
	{
		gameObjects.push_back((Segment*)&seg);
	}

	for (auto &npc : this->_npcs)
	{
		gameObjects.push_back((Box*)&npc.getBox());
	}

	this->_player.getBox().collide(gameObjects);

	for (auto &npc : this->_npcs)
	{
		npc.getBox().collide(gameObjects);
	}

	/* End of updating */
}

void Game::render()
{
	_graphics->fillBackground();

	/* Rendering of different classes */

	Point shift = this->_player.getBox().getFixedShift();

	for(int i = 0; i < boundingBox.size(); i++)
	{
		boundingBox[i].draw(*this->_graphics, shift);
	}

	this->_player.draw(*this->_graphics);

	for (auto &npc : this->_npcs)
	{
		npc.getBox().draw(*this->_graphics, shift);
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
