#include "sprite.hpp"
#include "graphics.hpp"
#include "util.hpp"
#include "rectangle.hpp"

#include <iostream>
#include <algorithm>

Sprite::Sprite()
{}

Sprite::~Sprite()
{
}

Sprite::Sprite(Graphics &graphics, const std::string path, Rectangle<int> sourceRect, float destWidth, float destHeight) :
	_destHeight(destHeight), _destWidth(destWidth), _sourceRect(sourceRect.toSDLRect())
{
	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));
}
void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destination = { x, y, (int) this->_destWidth, (int) this->_destHeight };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destination);
}