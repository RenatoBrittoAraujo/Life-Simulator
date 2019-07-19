#ifndef NPC_HPP
#define NPC_HPP

#include "life.hpp"

class NPC : public Life
{
public:

	NPC();
	~NPC();

	NPC(Graphics &graphics, const char *assetName, float width, float height);

	void update();
	void changeMovement();

private:

	void setRandomMovement(Util::Direction direction = Util::Direction::NONE);
	void moveRandomly();

	Util::Direction _randomMovementDirection = Util::Direction::NONE;

};

#endif
