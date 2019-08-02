#include "food.hpp"
#include "graphics.hpp"

float Food::randomLowerBound = 0.7;
float Food::randomUpperBound = 1.3;
float Food::nutritionalValueMultiplier = 500.0f;

Food::Food()
{}

Food::~Food()
{}

Food::Food(const char *assetName, float radius) :
	_size(Util::randFloat(randomLowerBound, randomUpperBound))
{
	this->init(assetName, radius * this->_size);
}

void Food::update()
{
	this->_circle.update();
}

int Food::getNutritionalValue() const 
{
	return (int)(this->_size * nutritionalValueMultiplier);
}