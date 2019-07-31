#include "food.hpp"
#include "graphics.hpp"

float Food::randomLowerBound = 0.7;
float Food::randomUpperBound = 1.3;
float Food::foodWeightMultiplier = 0.003f;

Food::Food()
{}

Food::~Food()
{
	for(auto follower : this->_followers)
	{
		follower->setTarget(nullptr);
	}
}

Food::Food(const char* assetName, float radius)
{
	float size = Util::randFloat(randomLowerBound, randomUpperBound);
	this->_size = size;
	this->_circle = new Circle(*Graphics::getInstance(), assetName, radius * size);
	this->_circle->setWeight(this->_circle->getWeight() * foodWeightMultiplier);
}

void Food::draw(Point shift)
{
	this->_circle->draw(*Graphics::getInstance(), shift);
}

void Food::update()
{
	this->_circle->update();
}

