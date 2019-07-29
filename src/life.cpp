#include "box.hpp"
#include "life.hpp"
#include "circle.hpp"
#include "collision.hpp"
#include "time.hpp"

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

void Life::draw(Graphics &graphics, Point shift)
{
	this->_circle.draw(graphics, shift);
}

void Life::update(unsigned int ticks)
{
	this->_circle.update();
	if(ticks - _lastUpdate > Time::secondToMilis(1))
	{
		this->_nourishment -= this->_nourishmentLossPerSecond;
	}
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
	this->_circle.setWeight(Circle::getSTDWeight() * size * size);
	this->_circle.setSpeedCap(Circle::getSTDSpeedCap() / size);
	this->_circle.setMovementSpeed(Circle::getSTDMovementSpeed() / size);
	this->_circle.setAttritionFactor(Circle::getSTDAttritionFactor() + (1.0 - size) * Circle::getSTDAttritionFactorDelta());
	this->_circle.updateSprite(graphics);
}

bool Life::isInFoodRadius(Food *food)
{
	if(food != nullptr and Collision::handleCollision(food->getCircle(), &this->_circle) and this->_eatsFood)
	{
		return true;
	}
	return false;
}