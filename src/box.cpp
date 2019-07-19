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
	setMovingObject(true);
	setCollidingObject(true);
	setUpdatingObject(true);
	this->_ySpeed = 0.0f;
	this->_xSpeed = 0.0f;
}

void Box::setSprite(Graphics &graphics, const char *assetName, int width, int height)
{
	Rectangle imageRect = this->images[std::string(assetName)];
	Rectangle sourceRect = imageRect;
	imageRect.fit(width, height);
	this->_width = imageRect.getWidth();
	this->_height = imageRect.getHeight();
	this->GameObject::setSprite(graphics, "assets/" + (std::string) assetName, sourceRect, imageRect.getWidth(), imageRect.getHeight());
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

#include <iostream>

void Box::move(Util::Direction direction)
{
	if(!direction)
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
			if(Collision::boxToBox(this, (Box*) object))
				std::cout<<"COLLISION BOX WITH BOX DETECTED"<<std::endl;
		}
		if(objectType == "Segment")
		{
			if (Collision::boxToSegment(this, (Segment *)object))
				std::cout << "COLLISION SEGMENT WITH BOX DETECTED" << std::endl;
		}
	}
}

// Private