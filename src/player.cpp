#include "player.hpp"
#include "life.hpp"

Player::Player()
{}

Player::~Player()
{}

Player::Player(Graphics &graphics, const char *assetName, float width, float height) : 
	Life(graphics, assetName, width, height)
{
	this->_box.setCentered(true);
}

const Point Player::getCenteredShift() const
{
	Point position = _box.getPosition();
	position.setX(position.getX() - (Util::getScreenWidth() / 2.0f - _box.getWidth() ));
	position.setY(position.getY() - (Util::getScreenHeight() / 2.0f - _box.getHeight() ));
	return position;
}