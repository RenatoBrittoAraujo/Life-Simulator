#include "gameobject.hpp"
#include "box.hpp"
#include "graphics.hpp"
#include "collision.hpp"

#include <string>
#include <vector>
#include <map>

// Public

Box::Box(Graphics &graphics, const char *assetName, float width, float height)
{
	setSprite(graphics, assetName, width, height);
	this->_width = width;
	this->_height = height;
	setMovingObject(true);
	setCollidingObject(true);
	setUpdatingObject(true);
}

void Box::setSprite(Graphics &graphics, const char *assetName, int width, int height)
{

	Rectangle imageRect = this->images[std::string(assetName)];
	Rectangle sourceRect = imageRect;
	imageRect.fit(width, height);
	this->GameObject::setSprite(graphics, assetName, sourceRect, imageRect.getWidth(), imageRect.getHeight());
}

void Box::draw(Graphics &graphics, Point shift)
{
	this->_sprite->draw(graphics, this->_x, this->_y);
}

void Box::update()
{
	this->_ySpeed = std::max(std::min(this->_ySpeed + PhysicsConstants::gravity, MovementConstants::speedCap), -MovementConstants::speedCap);
	this->_x += _xSpeed;
	this->_y += _ySpeed;
	this->_xSpeed *= MovementConstants::attritionFactor;
	this->_ySpeed *= MovementConstants::attritionFactor;
}

void Box::move(Util::Direction direction)
{
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

void Box::collide(std::vector<GameObject *> objects)
{
	for(auto &object : objects)
	{
		if(!object->collides() or this == object)
		{
			continue;
		}
		std::string objectType = object->type();
		if(objectType == "Box")
		{
			Collision::boxToBox(this, (Box*) object);
		}
		if(objectType == "Segment")
		{
			Collision::boxToSegment(this, (Segment *) object);
		}
	}
}

// Private