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

	void update();

	int getNutritionalValue() const;

	const std::string type() { return "FOOD"; }

	float getSize() const { return this->_size; }

private:

	static float randomLowerBound;
	static float randomUpperBound;

	static float foodWeightMultiplier;
	static float nutritionalValueMultiplier;

	float _size;
};

#endif