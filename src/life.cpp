#include "box.hpp"
#include "life.hpp"
#include "circle.hpp"
#include "collision.hpp"
#include "time.hpp"

const float Life::MIN_RANDOMIZE_FACTOR = 0.7;
const float Life::MAX_RANDOMIZE_FACTOR = 1.6;

Life::Life()
{}

Life::~Life()
{
	if (isFollowingSomething())
	{
		this->_target->removeFollower(this);
	}
	for (auto &follower : this->_followers)
	{
		follower->setTarget(nullptr);
	}
}

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
	this->_size = size;
	this->_circle.setWidth(size * this->_circle.getWidth());
	this->_circle.setHeight(size * this->_circle.getHeight());
	this->_circle.setRadius(size * this->_circle.getRadius());
	this->_circle.setWeight(Circle::getSTDWeight() * size * size);
	this->_circle.setSpeedCap(Circle::getSTDSpeedCap() / size);
	this->_circle.setMovementSpeed(Circle::getSTDMovementSpeed() / size);
	this->_circle.setAttritionFactor(Circle::getSTDAttritionFactor() + (1.0 - size) * Circle::getSTDAttritionFactorDelta());
	this->_circle.updateSprite(*Graphics::getInstance());
}

bool Life::targetInRadius(Life* target)
{
	if(target != nullptr and Collision::handleCollision(&target->getCircle(), &this->_circle, true /* NO HANDLING */))
	{
		return true;
	}
	return false;
}

void Life::addFollower(Life *newFollower)
{
	this->_followers.push_back(newFollower);
	newFollower->addFollowing(this);
}

void Life::removeFollower(Life *oldFollower)
{
	for (int i = 0; i < this->_followers.size(); i++)
	{
		if (this->_followers[i] == oldFollower)
		{
			this->_followers.erase(this->_followers.begin() + i);
			break;
		}
	}
}
void Life::addFollowing(Life *followTarget)
{
	this->_following.push_back(followTarget);
}

void Life::setTarget(Life *toFollow)
{
	this->_target = toFollow;
}

Life *Life::getTarget() const
{
	return this->_target;
}

bool Life::isFollowingSomething() const
{
	return this->_target != nullptr;
}

bool Life::hasFollowers() const
{
	return this->_followers.size() > 0;
}