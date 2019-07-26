#ifndef LIFE_HPP
#define LIFE_HPP

#include "circle.hpp"
#include "food.hpp"

#include <SDL2/SDL.h>

class Life
{
public:

	Life();
	~Life();

	Life(Graphics &graphics, const char *assetName, float radius);

	void draw(Graphics &graphics, Point shift = Point(0,0));
	virtual void update(unsigned int ticks = 0);

	Circle &getCircle() { return this->_circle; }

	void randomizeSize(Graphics &graphics, const float lowerBoundRandom = MIN_RANDOMIZE_FACTOR, const float upperBoundRandom = MAX_RANDOMIZE_FACTOR);

	void isInFoodRadius(Food &food);

	/*
		Standard size = 1.0
		0.0 means no size at all
		3.0 means original size ^ 3.0
	 */
	void setSize(Graphics &graphics, const float size);
	void setEatFood(const bool eatsFood) { this->_eatsFood = eatsFood; }
	int getNourishment() const { return this->_nourishment; }

protected:

	unsigned int _lastUpdate = SDL_GetTicks();

	void eat(Food &food);

	static const float MIN_RANDOMIZE_FACTOR;
	static const float MAX_RANDOMIZE_FACTOR;

	Circle _circle;

	bool _eatsFood = false;

	int _nourishment = 100;
	int _nourishmentLossPerSecond = 1;
};

#endif