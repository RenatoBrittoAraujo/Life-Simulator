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

	/*
		Process collisions between game objects
	 */
	void handleCollisions();

	bool _verbose;
	int _framerate;

	bool _isRunning;
	Graphics *_graphics;
	Input _input;

	SDL_Event _event;

	// Custom game classes

	Player _player;
	std::vector<NPC> _npcs;

	FoodManager foodManager = FoodManager::getInstance();
	std::vector<Life*> foodEaters;

	std::vector<Segment> boundingBox;

	unsigned int _ticksLastNpcMove;

	std::vector<GameObject*> collisionObjects;

	Globals &_globals = Globals::getInstance();

	// End of custom classes
};

#endif