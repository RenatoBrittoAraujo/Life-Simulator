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
	if(_centered)
	{
		this->_sprite->draw(graphics, Util::getScreenWidth() / 2.0f - this->_width, Util::getScreenHeight() / 2.0f - this->_height);
	}
	else
	{	
		this->_sprite->draw(graphics, this->_x - shift.getX(), this->_y - shift.getY());
	}
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
	if(!this->collides())
		return;
	for(auto &object : objects)
	{
		if(this == object)
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
			Collision::boxToSegment(this, (Segment *)object);
		}
	}
}

void Box::print()
{
	std::cout<<"BOX PARAMS:"<<std::endl;
	std::cout<<"\tX = "<<this->_x<<" Y = "<<this->_y<<" HEIGHT = "<<this->_height<<" WIDTH = "<<this->_width<<std::endl;
}

// Private