#include "food.hpp"
#include "graphics.hpp"

float Food::randomLowerBound = 0.7;
float Food::randomUpperBound = 1.3;

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