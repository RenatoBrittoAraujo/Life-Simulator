#include "util.hpp"
#include "vector2D.hpp"
#include "point.hpp"

#include <math.h>

Point::Point() {}
Point::~Point() {}

Point::Point(const float x, const float y) : _x(x), _y(y)
{}

float Point::getX() const { return this->_x; }
float Point::getY() const { return this->_y; }
void Point::setX(const float x) { this->_x = x; }
void Point::setY(const float y) { this->_y = y; }

/*
	Multiplies point's x and y by passed value
*/
void Point::scale(float scaleValue)
{
	this->_x *= scaleValue;
	this->_y *= scaleValue;
}

bool Point::operator<(const Point other) const
{
	return Util::fequals(this->_x, other.getX()) ? this->_y < other.getY() : this->_x < other.getX();
}

bool Point::operator==(const Point other) const
{
	return Util::fequals(this->_x, other.getX()) and Util::fequals(this->_y, other.getY());
}

float Point::euclidianDistance(const Point &other) const
{
	return hypot(this->getX() - other.getX(), this->getY() - other.getY());
}

void Point::traverseVector(const Vector2D &vector)
{
	this->_x += vector.getX();
	this->_y += vector.getY();
}
