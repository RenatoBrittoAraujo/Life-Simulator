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
	static const bool handleCollision(GameObject *objectA, GameObject *objectB, bool noHandling = false);

private:
	static const bool boxToBox(Box *boxA, Box *boxB, bool noHandling);
	static const bool boxToCircle(Box *box, Circle *circle, bool noHandling);
	static const bool boxToSegment(Box *box, Segment *segment, bool noHandling);
	static const bool circleToSegment(Circle *circle, Segment *segment, bool noHandling);
	static const bool circleToCircle(Circle *circleA, Circle *circleB, bool noHandling);
};

#endif