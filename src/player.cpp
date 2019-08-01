#include "player.hpp"
#include "life.hpp"

Player::Player()
{}

Player::~Player()
{}

Player::Player(const char *assetName, float radius) : 
	Life(assetName, radius)
{
	float adjustedRadius = this->getRadius();
	this->_circle.setFixed(true);
	this->_circle.setFixedPosition(Point(float(Util::getScreenWidth()) / 2.0f - adjustedRadius, float(Util::getScreenHeight()) / 2.0f - adjustedRadius));
	setEatFood(true);
}

void Player::move(Util::Direction direction)
{
	this->_circle.move(direction);
}