#include "npc.hpp"
#include "util.hpp"

NPC::NPC()
{}

NPC::~NPC()
{}

NPC::NPC(Graphics &graphics, const char *assetName, float radius) :
	Life(graphics, assetName, radius)
{
	setEatFood(true);
}

void NPC::update()
{
	moveRandomly();
	Life::update();
}

void NPC::changeMovement()
{
	setRandomMovement();
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

void NPC::moveRandomly()
{
	this->_circle.move(this->_randomMovementDirection);
}
