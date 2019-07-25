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
	this->_assetName = assetName;
}

void SpriteObject::updateSprite(Graphics &graphics)
{
	setSprite(graphics, this->_assetName, this->_width, this->_height);
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
	if (!this->updates())
	{
		return;
	}
	this->_ySpeed = std::max(std::min(this->_ySpeed + PhysicsConstants::gravity, this->_speedCap), -this->_speedCap);
	this->_x += _xSpeed;
	this->_y += _ySpeed;
	this->_xSpeed *= this->_attritionFactor;
	this->_ySpeed *= this->_attritionFactor;
}

void SpriteObject::move(Util::Direction direction)
{
	if (!direction or !this->moves())
	{
		return;
	}
	switch (direction)
	{
	case Util::Direction::BOTTOM:
		this->_ySpeed = std::min(
				this->_speedCap,
				this->_ySpeed + this->_movementSpeed);
		break;
	case Util::Direction::TOP:
		this->_ySpeed = std::max(
				-this->_speedCap,
				this->_ySpeed - this->_movementSpeed);
		break;
	case Util::Direction::LEFT:
		this->_xSpeed = std::max(
				-this->_speedCap,
				this->_xSpeed - this->_movementSpeed);
		break;
	case Util::Direction::RIGHT:
		this->_xSpeed = std::min(
				this->_speedCap,
				this->_xSpeed + this->_movementSpeed);
		break;
	default:
		break;
	}
}

/*
	This is a vector that stores information about specific images in assets/
	representing the source rectangle that is going to be cut from the image when read
 */

std::map<std::string, Rectangle<int>> SpriteObject::images({
	{"npcSquare.png", Rectangle<int>(0, 0, 512, 512)},
	{"playerSquare.png", Rectangle<int>(0, 0, 310, 310)},
	{"npcCircle.png", Rectangle<int>(0 , 0, 500, 500)},
	{"playerCircle.png", Rectangle<int>(0, 0, 500, 500)}
});

// Private

void SpriteObject::setSprite(Graphics &graphics, const std::string assetName, int width, int height)
{
	Rectangle<int> imageRect = this->images[std::string(assetName)];
	Rectangle<int> sourceRect = imageRect;
	imageRect.fit(width, height);
	this->_width = imageRect.getWidth();
	this->_height = imageRect.getHeight();
	this->_sprite = new Sprite(graphics, "assets/" + assetName, sourceRect, imageRect.getWidth(), imageRect.getHeight());
}
