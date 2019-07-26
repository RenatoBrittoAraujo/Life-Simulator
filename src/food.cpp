#include "food.hpp"

float Food::randomLowerBound = 0.7;
float Food::randomUpperBound = 1.3;

Food::Food()
{}

Food::~Food()
{}

Food::Food(Graphics &graphics, const char* assetName, float radius)
{
	this->_circle = Circle(graphics, assetName, radius);
	randomSize();
}

void Food::draw(Graphics &graphics)
{
	this->_circle.draw(graphics);
}

void Food::update()
{
	this->_circle.update();
}

void Food::randomSize(float lowerBound, float upperBound)
{
	float size = Util::randFloat(lowerBound, upperBound);
	this->_circle.setWidth(size * this->_circle.getWidth());
	this->_circle.setHeight(size * this->_circle.getHeight());
	this->_circle.setRadius(size * this->_circle.getRadius());
	this->_size = size;
}

void Food::eat()
{
	this->~Food();
}