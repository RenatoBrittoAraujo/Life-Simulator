#include "point.hpp"

#include <math.h>

Point::Point()
{
}

Point::~Point()
{
}

Point::Point(float x, float y) : _x(x), _y(y)
{
}

void Point::setX(float x)
{
	this->_x = x;
}

void Point::setY(float y)
{
	this->_y = y;
}

float Point::euclidianDistance(const Point &other) const
{
	return hypot(this->getX() - other.getX(), this->getY() - other.getY());
}

void Point::scale(float scaleValue)
{
	this->_x *= scaleValue;
	this->_y *= scaleValue;
}