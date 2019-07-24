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

Life::Life(Graphics &graphics, const char *assetName, float width, float height)
{
	this->_box = Circle(graphics, assetName, (width + height) / 2.0f);
	randomizeSize(graphics, 0.7, 2.0);
}

void Life::draw(Graphics &graphics)
{
	this->_box.draw(graphics);
}

void Life::update()
{
	this->_box.update();
}

void Life::randomizeSize(Graphics &graphics, const float lowerBoundRandom, const float upperBoundRandom)
{
	float ratio = Util::randFloat(lowerBoundRandom, upperBoundRandom);
	setSize(graphics, ratio);
}

void Life::setSize(Graphics &graphics, const float size)
{
	this->_box.setWidth(size * this->_box.getWidth());
	this->_box.setHeight(size * this->_box.getHeight());
	this->_box.setRadius(size * this->_box.getRadius());
	this->_box.setWeight(STD_WEIGHT * size * size);
	this->_box.setSpeedCap(STD_SPEED_CAP / size);
	this->_box.setMovementSpeed(STD_MOVEMENT_SPEED / size);
	this->_box.setAttritionFactor(STD_ATTRITION_FACTOR + (1.0 - size) * ATTRITION_FACTOR_DELTA);
	this->_box.updateSprite(graphics);
}