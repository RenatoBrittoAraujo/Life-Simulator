#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>
#include <map>

class Input
{
public:
	/*
		Clears key press and release data
	 */
	void beginNewFrame();

	/*
		Handles key up SDL event
	 */
	void keyUpEvent(const SDL_Event &event);

	/*
		Handles key down SDL event
	 */
	void keyDownEvent(const SDL_Event &event);

	/*
		Returns true if key was just pressed
	 */
	bool wasKeyPressed(SDL_Scancode key);

	/*
		Returns true if key was just released
	 */
	bool wasKeyReleased(SDL_Scancode key);

	/*
		Returns true if key is currently being pressed
	 */
	bool isKeyHeld(SDL_Scancode key);

private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
};

#endif