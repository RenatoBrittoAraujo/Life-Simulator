#ifndef NPC_HPP
#define NPC_HPP

#include "food.hpp"
#include "life.hpp"

#include <SDL2/SDL.h>

class NPC : public Life
{
public:

	NPC();
	~NPC();

	NPC(Graphics &graphics, const char *assetName, float radius);

	void update();

	unsigned int getMovementChangeDelta() const { return this->_movementChangeDelta; }
	void getMovementChangeDelta(const unsigned int movementChangeDelta) { this->_movementChangeDelta = movementChangeDelta; }
	void foodToFollow(std::vector<Food*> _foods);

	bool followingTarget() const { return !(this->_targetFollowing == nullptr); }

private:

	static unsigned int stdMovementChangeDelta;
	static float stdLineOfSight;

	/*
		if null, no target
		else currently following the target pointer
	*/
	Food* _targetFollowing = nullptr;

	void setRandomMovement(Util::Direction direction = Util::Direction::NONE);

	Util::Direction _randomMovementDirection = Util::Direction::NONE;

	unsigned int _lastMovementChange = SDL_GetTicks();
	unsigned int _movementChangeDelta = stdMovementChangeDelta;

	float _lineOfSight;

};

#endif
