#ifndef GAME_HPP
#define GAME_HPP

/* ENGINE HEADERS */
#include "fontobject.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "color.hpp"
#include "box.hpp"
#include "segment.hpp"

#include "foodmanager.hpp"
#include "globals.hpp"
#include "player.hpp"
#include "npc.hpp"
#include "food.hpp"
#include "preymanager.hpp"

#include <vector>

struct SDL_Window;
struct SDL_Renderer;

class Game
{
public:
	Game();
	~Game();

	bool init(bool fullscreen = true);

	/*
		Destroy current renderer and render, unload textures from GPU
	 */
	void exit();

	/*
		Returns true if game is currently running
	 */
	bool running();

	/*
		Runs main game loop
	 */
	void run();

	// Setters and Getters

	void setVerbose(bool verbose);
	void setFramerate(int framerate);
	void setScreenSize(int width, int height);

private:

	/*
		Configure starting game conditions such as spawn point and labirinth
	 */
	void startGame();

	/*
		Hanles user input as SDL's events
	*/
	void handleUserInput();

	/*
		Update all game objects
	 */
	void update();

	/*
		Render all game objects to screen
	 */
	void render();

	bool _verbose;
	int _framerate;

	bool _isRunning;
	Input _input;

	SDL_Event _event;

	/* Custom game classes */

	// In game objects
	Player _player;
	PreyManager _preyManager;
	std::vector<Segment> _boundingBox;
	FoodManager _foodManager;
	std::vector<CircleDecorator*> _foodEaters;
	FontObject _nourishmentDisplay;

	Graphics* _graphics;

	// Collision handling
	std::vector<GameObject*> collisionObjects;

	// Other settings
	Globals &_globals = Globals::getInstance();

	/* End of custom classes */
};

#endif