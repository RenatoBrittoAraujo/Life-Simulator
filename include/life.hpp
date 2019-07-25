#ifndef LIFE_HPP
#define LIFE_HPP

#include "box.hpp"
#include "circle.hpp"

class Life
{
public:

	Life();
	~Life();

	Life(Graphics &graphics, const char *assetName, float radius);

	virtual void draw(Graphics &graphics);
	virtual void update();

	Circle &getCircle() { return this->_circle; }

	void randomizeSize(Graphics &graphics, const float lowerBoundRandom = MIN_RANDOMIZE_FACTOR, const float upperBoundRandom = MAX_RANDOMIZE_FACTOR);

	/*
		Standard size = 1.0
		0.0 means no size at all
		3.0 means original size ^ 3.0
	 */
	void setSize(Graphics &graphics, const float size);

protected:

	static const float STD_MOVEMENT_SPEED;
	static const float STD_WEIGHT;
	static const float STD_ATTRITION_FACTOR;
	static const float STD_SPEED_CAP;

	static const float ATTRITION_FACTOR_DELTA;

	static const float MIN_RANDOMIZE_FACTOR;
	static const float MAX_RANDOMIZE_FACTOR;

	Circle _circle;

};

#endif