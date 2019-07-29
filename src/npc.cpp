#include "npc.hpp"
#include "util.hpp"

unsigned int NPC::stdMovementChangeDelta = 150;
float NPC::stdLineOfSight = 100.0f;

NPC::NPC()
{}

NPC::~NPC()
{}

NPC::NPC(Graphics &graphics, const char *assetName, float radius) :
	Life(graphics, assetName, radius)
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
		throw "Something really weird is going on";
	}
	else
	{
		unsigned int currentTime = SDL_GetTicks();
		if(currentTime - this->_lastMovementChange > this->_movementChangeDelta)
		{
			setRandomMovement();
			this->_lastMovementChange = currentTime;
		}
	}
	
	this->_circle.move(this->_randomMovementDirection);
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


