#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include "circledecorator.hpp"
#include "globals.hpp"
class Life;

#include <vector>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	EntityManager(int lowerEntityBound, int upperEntityBound, float EntityDensity);

	virtual void collide(std::vector<GameObject *> EntityColliders);
	virtual void update();
	void draw(Point shift);
	void eatCheck(std::vector<Life*> &EntityEaters);
	void reset(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect());
	void populate(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect(), int numberOfNewEntities = INVALID_AMOUNT);
	void destroy(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect());
	void addEntity(int numberOfNewEntitys, Rectangle<int> areaToAdd = Globals::getInstance().getGameMapRect());

	virtual CircleDecorator *newEntityInstance(Rectangle<int> areaToAdd) = 0;

	/*
    Getters and Setters
   */

	void setLowerEntityBound(const int lowerEntityBound) { this->_lowerEntityBound = lowerEntityBound; }
	void setUpperEntityBound(const int upperEntityBound) { this->_upperEntityBound = upperEntityBound; }
	void setEntityDensity(const float entityDensity) { this->_entityDensity = entityDensity; }
	int getLowerEntityBound() const { return this->_lowerEntityBound; }
	int getUpperEntityBound() const { return this->_upperEntityBound; }
	float getEntityDensity() const { return this->_entityDensity; }

	const std::vector<CircleDecorator*>& getTargets() const { return this->_entities; }

protected:

	static const int INVALID_AMOUNT = -1;

	std::vector<CircleDecorator*> _entities;

	void storeEntity(CircleDecorator* entity);
	void removeEntity(int index);

	float _entityDensity = 0.00001f;
	int _lowerEntityBound = 90;
	int _upperEntityBound = 100;
};

#endif