#ifndef FOOD_HPP
#define FOOD_HPP

#include "point.hpp"
#include "circledecorator.hpp"
#include "npc.hpp"

#include <string>
#include <vector>

class Food : public CircleDecorator
{
public:

	Food();
	~Food();

	Food(const char* assetName, float radius);

	void draw(Point shift = Point(0,0));
	void update();

	int getNutritionalValue() const { return (int) (this->_size * 100.0f); }

	const std::string type() { return "FOOD"; }

private:

	static float randomLowerBound;
	static float randomUpperBound;

	static float foodWeightMultiplier;

	float _size;
};

#endif