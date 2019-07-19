#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "box.hpp"
#include "segment.hpp"

class Collision
{
public:
	static const void boxToSegment(Box *box, Segment *segment);
	static const void boxToBox(Box *boxA, Box *boxB);
};

#endif