#ifndef FOOD_HPP
#define FOOD_HPP

#include "point.hpp"
#include "life.hpp"
#include "npc.hpp"
#include "color.hpp"

#include <string>
#include <vector>

class Food : public Life
{
public:

	Food();
	~Food();

	Food(float radius);

	void update();

	const std::string type() { return "FOOD"; }

	float getRot() const { return this->_rot; }

private:

	static const int rotLevels = 5;
	static float rotRate;

	static float foodWeightMultiplier;

	Color getRotShift();

	float _rot = 0.0;

};

#endif