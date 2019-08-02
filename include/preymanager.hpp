#ifndef PREYMANAGER_HPP
#define PREYMANAGER_HPP

#include "entitymanager.hpp"

class PreyManager : public EntityManager
{
public:
	PreyManager();
	~PreyManager();

	static PreyManager &getInstance();

	void update();
	void collide(std::vector<GameObject *> foodColliders);

	CircleDecorator *newEntityInstance(Rectangle<int> areaToAdd);

private:
	static PreyManager *instance;
};

#endif