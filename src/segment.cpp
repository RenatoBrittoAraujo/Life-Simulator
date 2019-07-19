#include "segment.hpp"
#include "point.hpp"
#include "util.hpp"

#include <SDL2/SDL.h>

Segment::Segment()
{

	setColor(Color::darkGray());
}

Segment::~Segment()
{
}

Segment::Segment(Point first, Point second)
{
	this->_first = first;
	this->_second = second;
	if (second < first)
	{
		std::swap(this->_first, this->_second);
	}
	setColor(Color::darkGray());
}

void Segment::draw(Graphics &graphics, Point currentShift)
{
	Color oldColor = graphics.getStandardColor();
	graphics.setRenderColor(getColor());
	SDL_RenderDrawLine(graphics.getRenderer(),
		_first.getX() - currentShift.getX(),
		_first.getY() - currentShift.getY(),
		_second.getX() - currentShift.getX(),
		_second.getY() - currentShift.getY());
	graphics.setRenderColor(oldColor);
}

void Segment::update()
{
}

void Segment::move(Util::Direction direction)
{
}

void Segment::collide(std::vector<GameObject *> objects)
{

}