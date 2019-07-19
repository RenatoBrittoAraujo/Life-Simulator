#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "box.hpp"
#include "segment.hpp"

class Collision
{
public:
	static const bool boxToSegment(Box *box, Segment *segment);
	static const bool boxToBox(Box *boxA, Box *boxB);
};

#endif