#ifndef POINT2D_HPP
#define POINT2D_HPP

#include "util.hpp"
class Vector2D;

#include <math.h>

class Point
{
public:

	Point();
	~Point();

	Point(const float x, const float y);

	float getX() const;
	float getY() const;
	void setX(const float x);
	void setY(const float y);

	/*
		Multiplies point's x and y by passed value
	 */
	void scale(float scaleValue);

	bool operator<(const Point other) const;

	bool operator==(const Point other) const;

	void traverseVector(const Vector2D &vector);

	float euclidianDistance(const Point &other) const;

private:
	float _x, _y;
};

#endif