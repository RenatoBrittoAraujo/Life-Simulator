#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "box.hpp"
#include "life.hpp"

class Player : public Life
{
public:

	Player();
	~Player();

	Player(const char *assetName, float radius);

	void move(Util::Direction direction);
	void update();

	virtual const std::string type() { return "PLAYER"; }
	
};

#endif