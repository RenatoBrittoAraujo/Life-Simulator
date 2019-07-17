#ifndef POINT_HPP
#define POINT_HPP

#include "util.hpp"

class Point
{
public:
	Point();
	~Point();

	Point(const float x, const float y);

	float getX() const { return this->_x; }
	float getY() const { return this->_y; }
	void setX(const float x);
	void setY(const float y);

	float euclidianDistance(const Point &other) const;

	/*
		Multiplies point's x and y by passed value
	 */
	void scale(const float scaleValue);

	bool operator<(const Point other) const
	{
		return Util::fequals(this->_x, other.getX()) ? this->_y < other.getY() : this->_x < other.getX();
	}

	bool operator==(const Point other) const
	{
		return Util::fequals(this->_x, other.getX()) and Util::fequals(this->_y, other.getY());
	}

private:
	float _x, _y;
};

#endif