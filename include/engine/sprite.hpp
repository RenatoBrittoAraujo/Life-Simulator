#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "graphics.hpp"
#include "rectangle.hpp"

#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Sprite
{
public:

	Sprite();
	~Sprite();

	Sprite(Graphics &graphics, const std::string path, Rectangle<int> sourceRect, float destWidth, float destHeight);
	Sprite(Graphics &graphics, const std::string path, float destWidth, float destHeight);

	/*
		Renders the sprite to screen
	 */
	void draw(Graphics &graphics, int x, int y);

protected:

	SDL_Rect _sourceRect;
	SDL_Texture *_spriteSheet;

private:

	float _destWidth;
	float _destHeight;

};

#endif