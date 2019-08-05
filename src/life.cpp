#include "box.hpp"
#include "life.hpp"
#include "circle.hpp"
#include "collision.hpp"
#include "time.hpp"

const float Life::MIN_RANDOMIZE_FACTOR = 0.5;
const float Life::MAX_RANDOMIZE_FACTOR = 2.0;

Life::Life()
{}

Life::~Life()
{}

Life::Life(const char *assetName, float radius) :
	CircleDecorator(assetName, radius)
{
	randomizeSize(0.7f, 2.0f);
}

void Life::update()
{
	this->_circle.update();
	if(Time::timeSince(_lastUpdate) > Time::secondToMilis(1))
	{
		this->_nourishment -= this->_nourishmentLossPerSecond;
		_lastUpdate = Time::current();
	}
}

void Life::randomizeSize(const float lowerBoundRandom, const float upperBoundRandom)
{
	float ratio = Util::randFloat(lowerBoundRandom, upperBoundRandom);
	setSize(ratio);
}

void Life::setSize(const float size)
{
	this->_circle.setWidth(size * this->_circle.getWidth());
	this->_circle.setHeight(size * this->_circle.getHeight());
	this->_circle.setRadius(size * this->_circle.getRadius());
	this->_circle.setWeight(Circle::getSTDWeight() * size * size);
	this->_circle.setSpeedCap(Circle::getSTDSpeedCap() / size);
	this->_circle.setMovementSpeed(Circle::getSTDMovementSpeed() / size);
	this->_circle.setAttritionFactor(Circle::getSTDAttritionFactor() + (1.0 - size) * Circle::getSTDAttritionFactorDelta());
	this->_circle.updateSprite(*Graphics::getInstance());
}

bool Life::targetInRadius(CircleDecorator* target)
{
	if(target != nullptr and Collision::handleCollision(&target->getCircle(), &this->_circle, true /* NO HANDLING */))
	{
		return true;
	}
	return false;
}