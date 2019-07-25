#ifndef FONT_HPP
#define FONT_HPP

#include "graphics.hpp"
#include "rectangle.hpp"
#include "color.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>

class Font
{
public:
	Font();
	~Font();

	/*
		Renders font to screen
	*/
	void draw(Graphics &graphics, SDL_Rect destRect);

	void update(Graphics &graphics, std::string text, std::string fontPath, int fontSize, Color fontColor);

private:

	TTF_Font* loadFont(std::string fontPath, int fontSize);
	SDL_Texture* _texture;
	static std::map< std::string, TTF_Font* > fonts;

};

#endif