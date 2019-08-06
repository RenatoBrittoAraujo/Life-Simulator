#ifndef PREDATORMANAGER_HPP
#define PREDATORMANAGER_HPP

#include "entitymanager.hpp"

class PredatorManager : public EntityManager
{
public:

	PredatorManager();
	~PredatorManager();

	static PredatorManager &getInstance();

	void update();

	Life *newEntityInstance(Rectangle<int> areaToAdd);

	void findFood(std::vector<Life *> _foods);
	void findFood(Life* food);

private:

	static PredatorManager *instance;

};

#endif