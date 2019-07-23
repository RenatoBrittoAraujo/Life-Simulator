#include "gameobject.hpp"
#include "spriteobject.hpp"
#include "graphics.hpp"

#include <string>
#include <vector>
#include <map>

// Public

SpriteObject::SpriteObject()
{
}

SpriteObject::~SpriteObject()
{

}

SpriteObject::SpriteObject(Graphics &graphics, const std::string assetName, float width, float height)
{
	setSprite(graphics, assetName, width, height);
	setMovingObject(true);
	setCollidingObject(true);
	setUpdatingObject(true);
	this->_ySpeed = 0.0f;
	this->_xSpeed = 0.0f;
	this->_fixed = false;
}

void SpriteObject::setSprite(Graphics &graphics, const std::string assetName, int width, int height)
{
	Rectangle imageRect = this->images[std::string(assetName)];
	Rectangle sourceRect = imageRect;
	imageRect.fit(width, height);
	this->_width = imageRect.getWidth();
	this->_height = imageRect.getHeight();
	this->_sprite = new Sprite(graphics, "assets/" + assetName, sourceRect, imageRect.getWidth(), imageRect.getHeight());
}

void SpriteObject::draw(Graphics &graphics, Point shift)
{
	if (this->_fixed)
	{
		this->_sprite->draw(graphics, this->_fixedPosition.getX(), this->_fixedPosition.getY());
	}
	else
	{
		this->_sprite->draw(graphics, this->_x - shift.getX(), this->_y - shift.getY());
	}
}

Point SpriteObject::getFixedShift() const
{
	Point position = getPosition();
	position.setX(position.getX() - getFixedPosition().getX());
	position.setY(position.getY() - getFixedPosition().getY());
	return position;
}

void SpriteObject::update()
{
	this->_ySpeed = std::max(std::min(this->_ySpeed + PhysicsConstants::gravity, MovementConstants::speedCap), -MovementConstants::speedCap);
	this->_x += _xSpeed;
	this->_y += _ySpeed;
	this->_xSpeed *= MovementConstants::attritionFactor;
	this->_ySpeed *= MovementConstants::attritionFactor;
}

void SpriteObject::move(Util::Direction direction)
{
	if (!direction)
		return;
	switch (direction)
	{
	case Util::Direction::BOTTOM:
		this->_ySpeed = std::min(
				MovementConstants::speedCap,
				this->_ySpeed + MovementConstants::movementAcceleration);
		break;
	case Util::Direction::TOP:
		this->_ySpeed = std::max(
				-MovementConstants::speedCap,
				this->_ySpeed - MovementConstants::movementAcceleration);
		break;
	case Util::Direction::LEFT:
		this->_xSpeed = std::max(
				-MovementConstants::speedCap,
				this->_xSpeed - MovementConstants::movementAcceleration);
		break;
	case Util::Direction::RIGHT:
		this->_xSpeed = std::min(
				MovementConstants::speedCap,
				this->_xSpeed + MovementConstants::movementAcceleration);
		break;
	default:
		break;
	}
}

std::map<std::string, Rectangle> SpriteObject::images({
	{"npcSquare.png", Rectangle(0.0f, 0.0f, 512.0f, 512.0f)},
	{"playerSquare.png", Rectangle(0.0f, 0.0f, 310.0f, 310.0f)},
	{"npcCircle.png", Rectangle(0.0f , 0.0f, 500.0f, 500.0f)},
	{"playerCircle.png", Rectangle(0.0f, 0.0f, 500.0f, 500.0f)}
});