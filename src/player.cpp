#include "player.hpp"
#include "life.hpp"

Player::Player()
{}

Player::~Player()
{}

Player::Player(Graphics &graphics, const char *assetName, float width, float height) : 
	Life(graphics, assetName, width, height)
{
	this->_box.setFixed(true);
	this->_box.setFixedPosition(Point(Util::getScreenWidth() / 2.0f - width / 2.0f, Util::getScreenHeight() / 2.0f - height / 2.0f));
}