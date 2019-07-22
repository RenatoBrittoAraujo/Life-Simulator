#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "box.hpp"
#include "segment.hpp"
#include "circle.hpp"

class Collision
{
public:
	/*
		Returns true if a collision happend and modifies the position of GameObjects accordingly
		Static gameobjects do not collide
	 */
	static const bool handleCollision(GameObject *objectA, GameObject *objectB);

private:
	static const bool boxToBox(Box *boxA, Box *boxB);
	static const bool boxToCircle(Box *box, Circle *circle);
	static const bool boxToSegment(Box *box, Segment *segment);
	static const bool circleToSegment(Circle *circle, Segment *segment);
	static const bool circleToCircle(Circle *circleA, Circle *circleB);
};

#endif