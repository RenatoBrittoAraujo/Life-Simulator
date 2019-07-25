#include "sprite.hpp"
#include "graphics.hpp"
#include "util.hpp"
#include "rectangle.hpp"

#include <iostream>
#include <algorithm>

Sprite::Sprite()
{}

Sprite::~Sprite()
{}

Sprite::Sprite(Graphics &graphics, const std::string path, Rectangle<int> sourceRect, float destWidth, float destHeight) :
	_destHeight(destHeight), _destWidth(destWidth), _sourceRect(sourceRect.toSDLRect())
{
	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));
}

Sprite::Sprite(Graphics &graphics, const std::string path, float destWidth, float destHeight) :
	_destHeight(destHeight), _destWidth(destWidth)
{
	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));
	this->_sourceRect = { 0, 0, 0, 0 };
}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destination = { x, y, (int) this->_destWidth, (int) this->_destHeight };
	if(this->_sourceRect.w == 0 or this->_sourceRect.h == 0)
	{
		graphics.blitSurface(this->_spriteSheet, NULL, &destination);
	}
	else
	{
		graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destination);
	}
}