#include "sprite.hpp"
#include "graphics.hpp"
#include "util.hpp"

#include <iostream>
#include <algorithm>

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

Sprite::Sprite(Graphics &graphics, const std::string &path, int sourceX, int sourceY, int width, int height, float scale)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_scale = scale;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));
	if (_spriteSheet == NULL)
	{
		throw "Failed at creating surface texture from path | Class: Sprite";
	}
}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destination = {x, y, Util::applyScale(this->_sourceRect.w, this->_scale), Util::applyScale(this->_sourceRect.h, this->_scale)};
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destination);
}