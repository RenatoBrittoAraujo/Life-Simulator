#include "player.hpp"
#include "life.hpp"

Player::Player()
{}

Player::~Player()
{}

Player::Player(Graphics &graphics, const char *assetName, float radius) : 
	Life(graphics, assetName, radius)
{
	float adjustedRadius = this->_circle.getRadius();
	this->_circle.setFixed(true);
	this->_circle.setFixedPosition(Point(float(Util::getScreenWidth()) / 2.0f - adjustedRadius, float(Util::getScreenHeight()) / 2.0f - adjustedRadius));
	setEatFood(true);
}

void Player::move(Util::Direction direction)
{
	this->_circle.move(direction);
}