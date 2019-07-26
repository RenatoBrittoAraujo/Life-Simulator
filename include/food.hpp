#ifndef FOOD_HPP
#define FOOD_HPP

#include "circle.hpp"
#include "point.hpp"

#include <string>

class Food
{
public:

	Food();
	~Food();

	Food(Graphics &graphics, const char* assetName, float radius);

	void draw(Graphics &graphics);
	void update();

	void eat();

	void randomSize(float lowerBound = randomLowerBound, float upperBound = randomUpperBound);

	Circle* getCircle() { return &this->_circle; }
	void setPosition(Point position) { this->_circle.setPosition(position); }
	int getNutritionalValue() const { return (int) (this->_size * 100.0f); }

private:

	static float randomLowerBound;
	static float randomUpperBound;

	float _size;
	Circle _circle;

};

#endif