#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "box.hpp"
#include "life.hpp"

class Player : public Life
{
public:

	Player();
	~Player();

	Player(Graphics &graphics, const char *assetName, float width, float height);

	/*
		Returns relative shift every object has to do in relation to centered object's position
	*/
	const Point getCenteredShift() const;
};

#endif