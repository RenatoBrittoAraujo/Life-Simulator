#include "npc.hpp"
#include "util.hpp"

unsigned int NPC::stdMovementChangeDelta = 150;
float NPC::stdLineOfSight = 300.0f;

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
}

void NPC::update()
{
	if (this->followingTarget())
	{
		this->followTarget();
	}
	else
	{
		unsigned int currentTime = SDL_GetTicks();
		if(currentTime - this->_lastMovementChange > this->_movementChangeDelta)
		{
			setRandomMovement();
			this->_lastMovementChange = currentTime;
		}
		this->_circle.move(this->_randomMovementDirection);
	}
	Life::update();
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
	if (this->followingTarget())
	{
		return;
	}
	CircleDecorator* validTarget = nullptr;
	for (auto &target : targets)
	{
		float distance = target->getPosition().euclidianDistance(this->getPosition());
		if (distance <= _lineOfSight and
				(validTarget == nullptr or 
				 validTarget->getPosition().euclidianDistance(this->getPosition()) > distance))
		{
			validTarget = target;
		}
	}
	this->_targetFollowing = validTarget;
	if (followingTarget())
	{
		this->_targetFollowing->addFollower(this);
	}
}

void NPC::followTarget()
{
	if(this->_targetFollowing == nullptr)
	{
		return;
	}
	Point npcPosition = this->getPosition();
	Point targetPosition = this->_targetFollowing->getPosition();
	float x = npcPosition.getX();
	float y = npcPosition.getY();
	Point top(x, y - 1);
	Point bottom(x, y + 1);
	Point left(x - 1, y);
	Point right(x + 1, y);
	std::vector<std::pair<float, Util::Direction>> directionToFollow =
	{
		{targetPosition.euclidianDistance(top) ,Util::Direction::TOP},
		{targetPosition.euclidianDistance(bottom) ,Util::Direction::BOTTOM},
		{targetPosition.euclidianDistance(left) ,Util::Direction::LEFT},
		{targetPosition.euclidianDistance(right) ,Util::Direction::RIGHT}
	};
	sort(directionToFollow.begin(), directionToFollow.end(), 
		[&] (std::pair<float, Util::Direction> a, std::pair<float, Util::Direction> b){
			return a.first < b.first;
	});
	Util::Direction movementDirection = directionToFollow[0].second;
	this->_circle.move(movementDirection);
}