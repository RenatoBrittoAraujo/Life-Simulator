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

	CircleDecorator *newEntityInstance(Rectangle<int> areaToAdd);

	void findFood(std::vector<CircleDecorator*> _foods);

private:
	static PreyManager *instance;
};

#endif