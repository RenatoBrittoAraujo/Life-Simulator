#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "point.hpp"
class Point;

class Vector2D
{
public:

	Vector2D();
	~Vector2D();

	Vector2D(const float x, const float y);

	Vector2D(const Point a, const Point b);

	/*
		Multiplies point's x and y by passed value
	 */
	void scale(const float &scaleValue);

	bool operator<(const Vector2D &other) const;

	bool operator==(const Vector2D &other) const;

	Vector2D operator+(const Vector2D &other) const;

	float dotProduct(const Vector2D &other) const;
	float crossProduct(const Vector2D &other) const;

	float getX() const;
	float getY() const;
	void setX(const float &x);
	void setY(const float &y);
	float getModulus() const;
	void setModulus(const float modulus);

private:

	float _x;
	float _y;

};

#endif