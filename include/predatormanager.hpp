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

	CircleDecorator *newEntityInstance(Rectangle<int> areaToAdd);

	void findFood(std::vector<CircleDecorator *> _foods);
	void findFood(CircleDecorator* food);

private:

	static PredatorManager *instance;

};

#endif