#ifndef LIFE_HPP
#define LIFE_HPP

#include "circledecorator.hpp"

#include <SDL2/SDL.h>
#include <memory>

class Life : public CircleDecorator
{
public:

	Life();
	~Life();

	Life(const char *assetName, float radius);

	virtual void update();

	void randomizeSize(const float lowerBoundRandom = MIN_RANDOMIZE_FACTOR, const float upperBoundRandom = MAX_RANDOMIZE_FACTOR);

	bool targetInRadius(CircleDecorator* target);

	/*
		Standard size = 1.0
		0.0 means no size at all
		3.0 means original size ^ 3.0
	 */
	void setSize(const float size);
	void setEatFood(const bool eatsFood) { this->_eatsFood = eatsFood; }
	void setNourishment(const int nourishment) { this->_nourishment = nourishment; }
	int getNourishment() const { return this->_nourishment; }

	/*
		Forcing implementation
	 */
	virtual const std::string type() const { return "LIFE"; };

protected:

	unsigned int _lastUpdate = SDL_GetTicks();

	static const float MIN_RANDOMIZE_FACTOR;
	static const float MAX_RANDOMIZE_FACTOR;

	bool _eatsFood = false;

	int _nourishment = 1000;
	int _nourishmentLossPerSecond = 15;
	
};

#endif