#include "box.hpp"
#include "life.hpp"
#include "circle.hpp"

const float Life::STD_MOVEMENT_SPEED = 0.9;
const float Life::STD_WEIGHT = 1.0;
const float Life::STD_ATTRITION_FACTOR = 0.95;
const float Life::STD_SPEED_CAP = 100.0;

const float Life::ATTRITION_FACTOR_DELTA = 0.01;

const float Life::MIN_RANDOMIZE_FACTOR = 0.5;
const float Life::MAX_RANDOMIZE_FACTOR = 2.0;

Life::Life()
{
}

Life::~Life()
{
}

Life::Life(Graphics &graphics, const char *assetName, float radius)
{
	this->_circle = Circle(graphics, assetName, radius);
	randomizeSize(graphics, 0.7, 2.0);
}

void Life::draw(Graphics &graphics)
{
	this->_circle.draw(graphics);
}

void Life::update()
{
	this->_circle.update();
}

void Life::randomizeSize(Graphics &graphics, const float lowerBoundRandom, const float upperBoundRandom)
{
	float ratio = Util::randFloat(lowerBoundRandom, upperBoundRandom);
	setSize(graphics, ratio);
}

void Life::setSize(Graphics &graphics, const float size)
{
	this->_circle.setWidth(size * this->_circle.getWidth());
	this->_circle.setHeight(size * this->_circle.getHeight());
	this->_circle.setRadius(size * this->_circle.getRadius());
	this->_circle.setWeight(STD_WEIGHT * size * size);
	this->_circle.setSpeedCap(STD_SPEED_CAP / size);
	this->_circle.setMovementSpeed(STD_MOVEMENT_SPEED / size);
	this->_circle.setAttritionFactor(STD_ATTRITION_FACTOR + (1.0 - size) * ATTRITION_FACTOR_DELTA);
	this->_circle.updateSprite(graphics);
}