#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "box.hpp"
#include "life.hpp"

class Player : public Life
{
public:

	Player();
	~Player();

	Player(Graphics &graphics, const char *assetName, float radius);
	
};

#endif