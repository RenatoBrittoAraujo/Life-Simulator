#include "npc.hpp"
#include "util.hpp"
#include "time.hpp"

unsigned int NPC::stdMovementChangeDelta = 150;
unsigned int NPC::stdScanForTargetTime = 50;
unsigned int NPC::stdFollowTargetTime = 150;
float NPC::stdLineOfSight = 300.0f;
unsigned int NPC::stdFleeDirectionUpdateRate = 200;

NPC::NPC()
{}

NPC::~NPC()
{}

NPC::NPC(const char *assetName, float radius) :
	Life(assetName, radius)
{
	setEatFood(true);
	this->_movementChangeDelta = stdMovementChangeDelta;
	setRandomMovement();
	this->_lineOfSight = stdLineOfSight;
	this->_targetFollowTime = stdFollowTargetTime;
	this->_targetScanTime = stdScanForTargetTime;
	this->_fleeDirectionUpdateRate = stdFleeDirectionUpdateRate;
}

void NPC::update()
{
	if (this->hasFollowers())
	{
		this->flee();
	}
	else if (isFollowingSomething())
	{
		this->hunt();
	}
	else
	{
		this->moveAimslessly();
	}
	this->Life::update();
}

void NPC::flee()
{
	this->setFleeDirection();
	this->_circle.move(this->_fleeDirection);
}

void NPC::hunt()
{
	followTarget();
	if (this->_targetFollowTime + this->_targetScanTime < Time::timeSince(this->_targetCycleTime))
	{
		this->_targetCycleTime = Time::current();
	}
}

void NPC::moveAimslessly()
{
	if (Time::timeSince(this->_lastMovementChange) > this->_movementChangeDelta)
	{
		setRandomMovement();
		this->_lastMovementChange = Time::current();
	}
	this->_circle.move(this->_randomMovementDirection);
}

void NPC::setRandomMovement(Util::Direction direction)
{
	int movementToken = Util::randInt(0, 100);
	if (movementToken < 50)
	{
		this->_randomMovementDirection = Util::Direction::NONE;
	}
	else if (movementToken < 50 / 4 + 50 or direction == Util::Direction::LEFT)
	{
		this->_randomMovementDirection = Util::Direction::LEFT;
	}
	else if (movementToken < 50 / 2 + 50 or direction == Util::Direction::RIGHT)
	{
		this->_randomMovementDirection = Util::Direction::RIGHT;
	}
	else if (movementToken < 50 / 2 + 50 / 4 + 50 or direction == Util::Direction::TOP)
	{
		this->_randomMovementDirection = Util::Direction::TOP;
	}
	else
	{
		this->_randomMovementDirection = Util::Direction::BOTTOM;
	}
}

void NPC::findTarget(const std::vector<CircleDecorator*> &targets)
{
	bool scanningPhase = Time::timeSince(this->_targetCycleTime) < this->_targetScanTime;
	if (isFollowingSomething() and !scanningPhase)
	{
		return;
	}
	CircleDecorator *validTarget = nullptr;
	for (auto &target : targets)
	{
		float distance = target->getPosition().euclidianDistance(this->getPosition());

		bool inLineOfSight = (distance <= this->_lineOfSight);
		bool targetNotFound = (validTarget == nullptr);
		bool newTargetCloserThanOlder = false;

		if(validTarget)
		{
			newTargetCloserThanOlder = (validTarget->getPosition().euclidianDistance(this->getPosition()) > distance);
		}

		if (inLineOfSight and (targetNotFound or newTargetCloserThanOlder))
		{
			validTarget = target;
		}
	}
	if (isFollowingSomething())
	{
		this->_target->removeFollower(this);
	}
	this->_target = validTarget;
	if (isFollowingSomething())
	{
		this->_target->addFollower(this);
	}
}

void NPC::followTarget()
{
	if(not isFollowingSomething())
	{
		return;
	}
	this->_circle.move(this->getDirection(this->_target->getPosition()));
}

void NPC::setFleeDirection()
{
	if (not this->hasFollowers() or Time::timeSince(this->_fleeDirectionLastUpdate) < this->_fleeDirectionUpdateRate)
	{
		return;
	}
	std::map<Util::Direction, int> followersByDirection;
	for (auto &follower : this->_followers)
	{
		if(follower->getPosition().euclidianDistance(this->getPosition()) > this->_lineOfSight)
		{
			continue;
		}
		followersByDirection[
			Util::getOppositeSide(this->getDirection(follower->getPosition()))
		]++;
	}
	if (followersByDirection.size() == 0)
	{
		this->_followers.clear();
		return;
	}
	int minimalFollowersDirection = Util::intMax();
	for (auto &iterator : followersByDirection)
	{
		minimalFollowersDirection = std::min(minimalFollowersDirection, iterator.second);
	}
	std::vector<Util::Direction> movementOptions;
	for (auto &iterator : followersByDirection)
	{
		if (iterator.second == minimalFollowersDirection)
		{
			movementOptions.push_back(iterator.first);
		}
	}
	Util::permute(movementOptions);
	this->_fleeDirectionLastUpdate = Time::current();
	this->_fleeDirection = movementOptions[0];
}

Util::Direction NPC::getDirection(Point target) const
{
	Point npcPosition = this->getPosition();
	float x = npcPosition.getX();
	float y = npcPosition.getY();
	Point top(x, y - 1);
	Point bottom(x, y + 1);
	Point left(x - 1, y);
	Point right(x + 1, y);
	std::vector<std::pair<float, Util::Direction>> directionToFollow =
	{
		{target.euclidianDistance(top) ,Util::Direction::TOP},
		{target.euclidianDistance(bottom) ,Util::Direction::BOTTOM},
		{target.euclidianDistance(left) ,Util::Direction::LEFT},
		{target.euclidianDistance(right) ,Util::Direction::RIGHT}
	};
	sort(directionToFollow.begin(), directionToFollow.end(), 
		[&] (std::pair<float, Util::Direction> a, std::pair<float, Util::Direction> b){
			return a.first < b.first;
	});
	Util::Direction movementDirection = directionToFollow[0].second;
	return movementDirection;
}