#include "life.hpp"
#include "sprite.hpp"
#include "segment.hpp"
#include "point.hpp"
#include "rectangle.hpp"

#include <algorithm>

// DEGUB ONLY ==================================================

#include <iostream>

// =============================================================

Life::Life()
{}

Life::~Life()
{}

// Rendering

void Life::loadSprite(Graphics &graphics, const char *assetName, const int imageWidth, int imageHeight, float scale)
{
	this->_sprite = new Sprite(graphics, assetName, 0, 0, imageHeight, imageWidth, scale);
	this->_height = Util::applyScale(imageHeight, scale);
	this->_width = Util::applyScale(imageWidth, scale);
}

void Life::draw(Graphics &graphics, Point currentShift)
{
	if (this->_centered)
	{
		this->_sprite->draw(graphics, 
			Util::getScreenWidth() / 2.0f - this->_width / 2.0f, 
			Util::getScreenHeight() / 2.0f - this->_height / 2.0f);
	}
	else
	{
		this->_sprite->draw(graphics, 
		this->_x - currentShift.getX(), 
		this->_y - currentShift.getY());
	}
}

// Movement mechanics

namespace LifeMovementParams
{
const float lifeSpeedCap = 1000.0;
const float lifeAcceleration = 0.9;
const float gravity = 0.00;
const float slowDownFactor = 0.8;
const float attritionFactor = 0.90;
}

void Life::update()
{
	this->moveRandomly();
	this->_ySpeed = std::max(std::min(this->_ySpeed + LifeMovementParams::gravity, LifeMovementParams::lifeSpeedCap), -LifeMovementParams::lifeSpeedCap);
	this->_x += _xSpeed;
	this->_y += _ySpeed;
	this->_xSpeed *= LifeMovementParams::attritionFactor;
	this->_ySpeed *= LifeMovementParams::attritionFactor;
}

void Life::setRandomMovement(Util::Direction direction)
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

void Life::moveRandomly()
{
	switch(this->_randomMovementDirection)
	{
	case Util::Direction::BOTTOM:
		this->moveDown();
		break;
	case Util::Direction::TOP:
		this->moveUp();
		break;
	case Util::Direction::LEFT:
		this->moveLeft();
		break;
	case Util::Direction::RIGHT:
		this->moveRight();
		break;
	default:
		break;
	}
}

const Point Life::getCenteredShift() const
{
	Point position = this->getPosition();
	position.setX(position.getX() - (Util::getScreenWidth() / 2.0f - this->_width / 2.0f));
	position.setY(position.getY() - (Util::getScreenHeight() / 2.0f - this->_height / 2.0f));
	return position;
}

void Life::moveDown()
{
	this->_ySpeed = std::min(
			LifeMovementParams::lifeSpeedCap, 
			this->_ySpeed + LifeMovementParams::lifeAcceleration);
}

void Life::moveUp()
{
	this->_ySpeed = std::max(
			-LifeMovementParams::lifeSpeedCap,
			this->_ySpeed - LifeMovementParams::lifeAcceleration);
}

void Life::moveLeft()
{
	this->_xSpeed = std::max(
			-LifeMovementParams::lifeSpeedCap,
			this->_xSpeed - LifeMovementParams::lifeAcceleration);
}

void Life::moveRight()
{
	this->_xSpeed = std::min(
			LifeMovementParams::lifeSpeedCap,
			this->_xSpeed + LifeMovementParams::lifeAcceleration);
}

// Collision Mechanics

void Life::collisionCheck(std::vector<Segment> barriers, std::vector<Life *> lives)
{
	for (auto segment : barriers)
	{
		this->handleSegmentCollision(segment);
	}
	for (Life *life : lives)
	{
		this->handleLifeCollision(life);
	}
}

void Life::handleSegmentCollision(Segment segment)
{
	const float fx = segment.getFirst().getX();
	const float fy = segment.getFirst().getY();
	const float sx = segment.getSecond().getX();
	const float sy = segment.getSecond().getY();

	float x = _x + _width / 2.0f;
	float y = _y + _height / 2.0f;
	float halfWidth = _width / 2.0f;
	float halfHeight = _height / 2.0f;

	if (Util::fequals(fx, sx))
	{
		float segx = fx;
		if (segx >= x - halfWidth and segx <= x + halfWidth and
				std::min(fy, sy) < y + halfHeight and std::max(fy, sy) > y - halfHeight)
		{
			this->_xSpeed = -this->_xSpeed * LifeMovementParams::slowDownFactor;
			if (segx - (x - halfWidth) > x + halfWidth - segx)
			{
				// LEFT COLLISION
				x = segx - halfWidth;
			}
			else
			{
				// RIGHT COLLISION
				x = segx + halfWidth;
			}
		}
	}
	else
	{
		float segy = fy;
		if (segy >= y - halfHeight and segy <= y + halfHeight and
				std::min(fx, sx) < x + halfWidth and std::max(fx, sx) > x - halfWidth)
		{
			this->_ySpeed = -this->_ySpeed * LifeMovementParams::slowDownFactor;
			if (segy - (y - halfHeight) > y + halfHeight - segy)
			{
				// BOTTOM COLLISION
				y = segy - halfHeight;
			}
			else
			{
				// TOP COLLISION
				y = segy + halfHeight;
			}
		}
	}

	_x = x - halfWidth;
	_y = y - halfHeight;
}

void Life::handleLifeCollision(Life *life)
{
	const Rectangle orgRect = this->getBoundingBox();
	const Rectangle tgtRect = life->getBoundingBox();

	if(!orgRect.collidesWith(tgtRect) or orgRect == tgtRect)
		return;

	float recoil = orgRect.collisionLength(tgtRect) / 2.0f;
	float momentum;

	switch (orgRect.collisionSide(tgtRect))
	{
	case Util::Direction::TOP:
		this->_y = this->_y + recoil;
		life->setY(life->getY() - recoil);
		momentum = -this->_ySpeed + life->getYSpeed();
		this->_ySpeed = + momentum / 2.0f;
		life->setYSpeed(-momentum / 2.0f);
		break;

	case Util::Direction::BOTTOM:
		this->_y = this->_y - recoil;
		life->setY(life->getY() + recoil);
		momentum = this->_ySpeed - life->getYSpeed();
		this->_ySpeed = - momentum / 2.0f;
		life->setYSpeed(+momentum / 2.0f);
		break;

	case Util::Direction::LEFT:
		this->_x = this->_x + recoil;
		life->setX(life->getX() - recoil);
		momentum = -this->_xSpeed + life->getXSpeed();
		this->_xSpeed = + momentum / 2.0f;
		life->setXSpeed(-momentum / 2.0f);
		break;

	case Util::Direction::RIGHT:
		this->_x = this->_x - recoil;
		life->setX(life->getX() + recoil);
		momentum = this->_xSpeed - life->getXSpeed();
		this->_xSpeed = - momentum / 2.0f;
		life->setXSpeed(+momentum / 2.0f);
		break;

	default:
		break;
	}
}