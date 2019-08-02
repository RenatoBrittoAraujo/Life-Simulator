#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include "circledecorator.hpp"
#include "globals.hpp"
#include "gameobject.hpp"

class Life;

#include <vector>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	EntityManager(int lowerEntityBound, int upperEntityBound, float EntityDensity);

	void collide(std::vector<GameObject *> &entityColliders);
	virtual void update();
	void draw(Point shift);
	void reset(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect());
	void populate(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect(), int numberOfNewEntities = INVALID_AMOUNT);
	void destroy(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect());
	void addEntity(int numberOfNewEntitys, Rectangle<int> areaToAdd = Globals::getInstance().getGameMapRect());

	void eatCheck(std::vector<CircleDecorator*> &entityEaters);
	void eatCheck(CircleDecorator *entityEater);

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

	std::vector<CircleDecorator*>& getEntities() { return this->_entities; }
	std::vector<GameObject*>& getCollisionObjects() { return this->_entitiesObjects; }

protected:

	static const int INVALID_AMOUNT = -1;

	std::vector<CircleDecorator*> _entities;
	std::vector<GameObject*> _entitiesObjects;

	void storeEntity(CircleDecorator* entity);
	void removeEntity(int index);

	float _entityDensity;
	int _lowerEntityBound;
	int _upperEntityBound;
};

#endif