#include "fontobject.hpp"

#include "gameobject.hpp"
#include "font.hpp"
#include "color.hpp"

#include <SDL2/SDL.h>
#include <string>

FontObject::FontObject()
{}

FontObject ::~FontObject()
{}

FontObject::FontObject(Graphics &graphics, float width, float height, std::string text) :
	_width(width), _height(height), _text(text)
{
	this->_font.update(graphics, text, this->_fontPath, this->_fontSize, this->_fontColor);
}

FontObject::FontObject(float width, float height) :
	_width(width), _height(height)
{}

void FontObject::update(Graphics &graphics, std::string text)
{
	this->_font.update(graphics, text, this->_fontPath, this->_fontSize, this->_fontColor);
}

void FontObject::draw(Graphics &graphics, Point shift)
{
	this->_font.draw(graphics, getBoundingBox().toSDLRect());
}