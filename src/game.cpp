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
	const int MIN_NPC = 50;
	const int MAX_NPC = 100;
	const int SPAWN_BORDER_DISTANCE = 40;
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
	_player = Player("assets/playerCircle.png", 25.0f);

	_player.getCircle().setPosition(Point(200,100));

	// Setting up NPCs
	for(int i = 0; i < Util::randInt(GameMap::MIN_NPC, GameMap::MAX_NPC); i++)
	{
		NPC npc = NPC("assets/npcCircle.png", 20.0f);
		npc.getCircle().setPosition(Point(Util::randInt(50, GameMap::MAP_WIDTH - 50), Util::randInt(50, GameMap::MAP_HEIGHT)));
		this->_npcs.push_back(npc);
	}
	
	for(auto &npc : this->_npcs)
	{
		this->_foodEaters.push_back(&npc);
	}

	this->_foodEaters.push_back(&this->_player);

	// Setting up food
	this->_foodManager = FoodManager::getInstance();

	this->_foodManager.populate();


	// Set up map borders
	this->_boundingBox = {
	Segment(Point(0, 0), Point(0, GameMap::MAP_HEIGHT)),
	Segment(Point(GameMap::MAP_WIDTH, GameMap::MAP_HEIGHT), Point(0, GameMap::MAP_HEIGHT)),
	Segment(Point(GameMap::MAP_WIDTH, GameMap::MAP_HEIGHT), Point(GameMap::MAP_WIDTH, 0)),
	Segment(Point(0, 0), Point(GameMap::MAP_WIDTH, 0))};

	this->collisionObjects.push_back(&this->_player.getCircle());

	for (auto &seg : this->_boundingBox)
	{
		this->collisionObjects.push_back(&seg);
	}

	for (auto &npc : this->_npcs)
	{
		this->collisionObjects.push_back(&npc.getCircle());
	}

	this->_player.setNourishment(100);
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
	this->_player.update();

	for(auto& npc : this->_npcs)
	{
		npc.update();
		npc.findTarget(this->_foodManager.getTargets());
	}

	this->_foodManager.eatCheck(this->_foodEaters);

	this->_foodManager.update();

	handleCollisions();
}

void Game::handleCollisions()
{
	for(auto &object : collisionObjects)
	{
		object->collide(collisionObjects);
	}
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

	for (auto &npc : this->_npcs)
	{
		npc.draw(shift);
	}

	this->_foodManager.draw(shift);

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