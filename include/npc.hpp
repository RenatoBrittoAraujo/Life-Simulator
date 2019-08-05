#ifndef NPC_HPP
#define NPC_HPP

#include "food.hpp"
#include "life.hpp"
#include "circledecorator.hpp"
#include "time.hpp"

class NPC : public Life
{
public:

	NPC();
	~NPC();

	NPC(const char *assetName, float radius);

	void update();

	unsigned int getMovementChangeDelta() const { return this->_movementChangeDelta; }
	void getMovementChangeDelta(const unsigned int movementChangeDelta) { this->_movementChangeDelta = movementChangeDelta; }

	virtual const std::string type() { return "NPC"; }

	void findTarget(const std::vector<CircleDecorator*> &targets);

private:

	static unsigned int stdMovementChangeDelta;
	static float stdLineOfSight;
	static unsigned int stdScanForTargetTime;
	static unsigned int stdFollowTargetTime;

	void followTarget();

	void setRandomMovement(Util::Direction direction = Util::Direction::NONE);

	Util::Direction _randomMovementDirection = Util::Direction::NONE;

	unsigned int _lastMovementChange = Time::current();
	unsigned int _movementChangeDelta = stdMovementChangeDelta;
	
	unsigned int _targetScanTime;
	unsigned int _targetFollowTime;
	unsigned int _targetCycleTime = Time::current();

	float _lineOfSight;

};

#endif
