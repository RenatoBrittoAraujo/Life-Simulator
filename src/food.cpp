#include "food.hpp"
#include "graphics.hpp"

float Food::randomLowerBound = 0.7;
float Food::randomUpperBound = 1.3;
float Food::foodWeightMultiplier = 0.003f;
float Food::nutritionalValueMultiplier = 500.0f;

Food::Food()
{}

Food::~Food()
{
	for(auto follower : this->_followers)
	{
		follower->setTarget(nullptr);
	}
}

Food::Food(const char *assetName, float radius) :
	_size(Util::randFloat(randomLowerBound, randomUpperBound)), 
	CircleDecorator(assetName, radius * this->_size)
{
	this->setWeight(this->getWeight() * foodWeightMultiplier);
}

void Food::update()
{
	this->_circle.update();
}

int Food::getNutritionalValue() const 
{
	return (int)(this->_size * nutritionalValueMultiplier);
}