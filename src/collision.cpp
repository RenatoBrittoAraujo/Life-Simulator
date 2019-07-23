#include "collision.hpp"
#include "box.hpp"
#include "segment.hpp"
#include "util.hpp"
#include "rectangle.hpp"
#include "point.hpp"
#include "circle.hpp"
#include "gameobject.hpp"
#include "vector2D.hpp"

#include <vector>
#include <algorithm>

const float pi = acos(-1.0);

/*
	Notes on segment collisions:
	Segments are assumed to be fixed
	This is not to be the case forever but
	segment movement is a complicated topic
	and will be worked on in the future
 */

// Public

const bool Collision::handleCollision(GameObject *objectA, GameObject *objectB)
{
	// If any of the objects are an instance of the virtual class GameObject or 
	// both objects are actually the same or
	// none of the objects would move if a collision was to happen
	// return no collision and don't calculate anything
	if (objectA->type() == GAMEOBJECT or
			objectB->type() == GAMEOBJECT or
			objectA == objectB or
			(objectA->collides() == false and objectB->collides() == false))
	{
		return false;
	}
	// Swapping them for easier comparing
	if (objectA->type() > objectB->type())
	{
		std::swap(objectA, objectB);
	}
	// Hardcoded handlers
	if (objectA->type() == BOX and objectB->type() == BOX)
	{
		return boxToBox((Box *)objectA, (Box *)objectB);
	}
	if (objectA->type() == BOX and objectB->type() == CIRCLE)
	{
		return boxToCircle((Box *)objectA, (Circle *)objectB);
	}
	if (objectA->type() == BOX and objectB->type() == SEGMENT)
	{
		return boxToSegment((Box *)objectA, (Segment *)objectB);
	}
	if (objectA->type() == CIRCLE and objectB->type() == CIRCLE)
	{
		return circleToCircle((Circle *)objectA, (Circle *)objectB);
	}
	if (objectA->type() == CIRCLE and objectB->type() == SEGMENT)
	{
		return circleToSegment((Circle *)objectA, (Segment *)objectB);
	}
	return false;
}
// Private

const bool Collision::boxToBox(Box *boxA, Box *boxB)
{
	const Rectangle boxARect = boxA->getBoundingBox();
	const Rectangle boxBRect = boxB->getBoundingBox();

	if(!boxARect.collidesWith(boxBRect) or boxARect == boxBRect)
		return false;

	float recoil = boxARect.collisionLength(boxBRect) / 2.0f;
	float momentum;

	switch (boxARect.collisionSide(boxBRect))
	{
	case Util::Direction::TOP:
		boxA->setY(boxA->getY() + recoil);
		boxB->setY(boxB->getY() - recoil);
		momentum = -boxA->getYSpeed() + boxB->getYSpeed();
		boxA->setYSpeed(+ momentum / 2.0f);
		boxB->setYSpeed(-momentum / 2.0f);
		break;

	case Util::Direction::BOTTOM:
		boxA->setY(boxA->getY() - recoil);
		boxB->setY(boxB->getY() + recoil);
		momentum = boxA->getYSpeed() - boxB->getYSpeed();
		boxA->setYSpeed(- momentum / 2.0f);
		boxB->setYSpeed(+momentum / 2.0f);
		break;

	case Util::Direction::LEFT:
		boxA->setX(boxA->getX() + recoil);
		boxB->setX(boxB->getX() - recoil);
		momentum = -boxA->getXSpeed() + boxB->getXSpeed();
		boxA->setXSpeed(+ momentum / 2.0f);
		boxB->setXSpeed(-momentum / 2.0f);
		break;

	case Util::Direction::RIGHT:
		boxA->setX(boxA->getX() - recoil);
		boxB->setX(boxB->getX() + recoil);
		momentum = boxA->getXSpeed() - boxB->getXSpeed();
		boxA->setXSpeed(- momentum / 2.0f);
		boxB->setXSpeed(+momentum / 2.0f);
		break;

	default:
		return false;
		break;
	}
	return true;
}

const bool Collision::boxToSegment(Box *box, Segment *segment)
{
	const float fx = segment->getFirst().getX();
	const float fy = segment->getFirst().getY();
	const float sx = segment->getSecond().getX();
	const float sy = segment->getSecond().getY();

	float x = box->getX() + box->getWidth() / 2.0f;
	float y = box->getY() + box->getHeight() / 2.0f;
	float halfWidth = box->getWidth() / 2.0f;
	float halfHeight = box->getHeight() / 2.0f;

	if (Util::fequals(fx, sx))
	{
		float segx = fx;
		if (segx >= x - halfWidth and segx <= x + halfWidth and
				std::min(fy, sy) < y + halfHeight and std::max(fy, sy) > y - halfHeight)
		{
			box->setXSpeed(-box->getXSpeed() * PhysicsConstants::bounceSpeedFactor);
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
			box->setYSpeed(-box->getYSpeed() * PhysicsConstants::bounceSpeedFactor);
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

	if (Util::fequals(x - halfWidth, box->getX()) and Util::fequals(y - halfHeight, box->getY()))
		return false;

		box->setX(x - halfWidth);
	box->setY(y - halfHeight);
	return true;
}

const bool Collision::boxToCircle(Box *box, Circle *circle)
{

}

const bool Collision::circleToCircle(Circle *circleA, Circle *circleB)
{
	float ra = circleA->getRadius();
	float rb = circleB->getRadius();
	float xa = circleA->getX() + ra;
	float ya = circleA->getY() + ra;
	float xb = circleB->getX() + rb;
	float yb = circleB->getY() + rb;

	Point centerA = Point(xa, ya);
	Point centerB = Point(xb, yb);

	float dist = centerA.euclidianDistance(centerB);

	if (dist > ra + rb)
	{
		return false;
	}

	Vector2D vecFromAtoB(centerA, centerB);

	vecFromAtoB.scale( (ra + rb - dist) / (dist * 2.0f) );

	Point newBPos(circleB->getPosition());
	newBPos.traverseVector(vecFromAtoB);
	circleB->setPosition(newBPos);

	vecFromAtoB.scale(-1.0f);
	
	Point newAPos(circleA->getPosition());
	newAPos.traverseVector(vecFromAtoB);
	circleA->setPosition(newAPos);

	return true;
}

const bool Collision::circleToSegment(Circle *circle, Segment *segment)
{
	float cx = circle->getX();
	float cy = circle->getY();
	float r = circle->getRadius();
	Vector2D vectorAtoB((Point) segment->getFirst(), segment->getSecond());
	Point circleCenter(cx + r, cy + r);
	Vector2D vectorAtoCenter(segment->getFirst(), circleCenter);
	float epislon = vectorAtoCenter.dotProduct(vectorAtoB) / vectorAtoB.dotProduct(vectorAtoB);
	
	Point closest;
	Vector2D speed = circle->getSpeed();
	bool speedSet = false;
	if (epislon < 0.0f or epislon > 1.0f)
	{
		closest = segment->getFirst();
		if (circleCenter.euclidianDistance(segment->getSecond()) < 
				circleCenter.euclidianDistance(closest))
			closest = segment->getSecond();
	}
	else
	{
		closest = Point(segment->getFirst());
		vectorAtoB.scale(epislon);
		closest.traverseVector(vectorAtoB);
	}

	float dist = closest.euclidianDistance(circleCenter);
	if (dist > r)
	{
		return false;
	}
	Vector2D moveBack(closest, circleCenter);
	moveBack.scale((r - dist) / dist + 0.001f);
	Point newPos = circle->getPosition();
	newPos.traverseVector(moveBack);
	circle->setPosition(newPos);
	Vector2D vectorCenterToClosest(circleCenter, closest);
	float angle = 
		atan2(
			vectorCenterToClosest.crossProduct(speed),
			vectorCenterToClosest.dotProduct(speed)
		);
	angle = pi - 2.0f * angle;
	float newX = speed.getX() * cos(angle) - speed.getY() * sin(angle);
	float newY = speed.getX() * sin(angle) + speed.getY() * cos(angle);
	speed = Vector2D(newX, newY);
	speed.scale(PhysicsConstants::bounceSpeedFactor);
	circle->setSpeed(speed);
	return true;
}