#include "util.hpp"
#include "vector2D.hpp"
#include "point.hpp"

Vector2D::Vector2D() {}
Vector2D::~Vector2D() {}

Vector2D::Vector2D(const float x, const float y)
{
	this->_x = x;
	this->_y = y;
}

Vector2D::Vector2D(const Point a, const Point b)
{
	this->_x = b.getX() - a.getX();
	this->_y = b.getY() - a.getY();
}

/*
	Multiplies point's x and y by passed value
*/
void Vector2D::scale(const float &scaleValue)
{
	this->_x *= scaleValue;
	this->_y *= scaleValue;
}

bool Vector2D::operator<(const Point &other) const
{
	return Util::fequals(this->_x, other.getX()) ? this->_y < other.getY() : this->_x < other.getX();
}

bool Vector2D::operator==(const Point &other) const
{
	return Util::fequals(this->_x, other.getX()) and Util::fequals(this->_y, other.getY());
}

float Vector2D::dotProduct(const Vector2D &other) const
{
	return this->_x * other.getX() + this->_y * other.getY();
}

float Vector2D::crossProduct(const Vector2D &other) const
{
	return this->_x * other.getY() - this->_y * other.getX();
}

float Vector2D::getX() const { return this->_x; }
float Vector2D::getY() const { return this->_y; }
void Vector2D::setX(const float &x) { this->_x = x; }
void Vector2D::setY(const float &y) { this->_y = y; }

