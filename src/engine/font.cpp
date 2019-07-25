#include "font.hpp"
#include "graphics.hpp"
#include "util.hpp"
#include "rectangle.hpp"
#include "color.hpp"

#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

std::map<std::string, TTF_Font *> Font::fonts = std::map<std::string, TTF_Font *>();

Font::Font()
{
}

Font::~Font()
{
	SDL_DestroyTexture(this->_texture);
}

void Font::draw(Graphics &graphics, SDL_Rect rect)
{
	graphics.blitSurface(this->_texture, nullptr, &rect);
}

void Font::update(Graphics &graphics, std::string text, std::string fontPath, int fontSize, Color fontColor)
{
	SDL_DestroyTexture(this->_texture);
	TTF_Font *font = loadFont(fontPath, fontSize);
	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), fontColor.toSDLColor());
	this->_texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
}

TTF_Font* Font::loadFont(std::string fontPath, int fontSize)
{
	if (this->fonts[fontPath] != NULL)
	{
		return this->fonts[fontPath];
	}
	else
	{
		return this->fonts[fontPath] = TTF_OpenFont(fontPath.c_str(), fontSize);
	}
}