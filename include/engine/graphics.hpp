#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "color.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>

class Graphics
{
public:

	Graphics(const char *windowTitle, bool fullscreen = true, int screenWidth = 0, int screenHeight = 0);
	~Graphics();

	static Graphics* getInstance()
  {
		if (_instance == nullptr)
		{
			throw "Graphics instance null";
		}
    return _instance;
  }

	static void setInstance(Graphics* receivedInstance)
	{
		_instance = receivedInstance;
	}

	/*
		Loads image and stores it as texture in graphic card
	 */
	SDL_Surface *loadImage(const std::string &path);

	/*
		Place na image in renderer
	 */
	void blitSurface(SDL_Texture *source, SDL_Rect *sourceRectagle, SDL_Rect *destinationRectangle);

	/*
		Renders renderer to screen
	 */
	void flip();

	/*
		Fills renderer background with set background color
	 */
	void fillBackground();
	
	/*
		Getters and setters
	 */

	SDL_Renderer *getRenderer() const;
	void setRenderColor(Color color);

	void setStandardColor(const Color color) { this->_standardColor = color; }
	Color getStandardColor() const { return this->_standardColor; }

private:

	static Graphics* _instance;

	SDL_Window *_window;
	SDL_Renderer *_renderer;

	std::map<std::string, SDL_Surface *> _spriteSheets;

	Color _standardColor = Color(255,255,255,255);
};

#endif