#include "predatormanager.hpp"
#include "predator.hpp"

PredatorManager *PredatorManager::instance = nullptr;

PredatorManager::PredatorManager()
{}

PredatorManager::~PredatorManager()
{}

void PredatorManager::update()
{
	for (auto &predator : this->_entities)
	{
		predator->update();
	}
	// if (this->_entities.size() < this->_lowerEntityBound)
	// {
	// 	addEntity(this->_lowerEntityBound - this->_entities.size());
	// }
}

void PredatorManager::findFood(std::vector<CircleDecorator *> foods)
{
	for (auto &predator : this->_entities)
	{
		((Predator *)predator)->findTarget(foods);
	}
}

void PredatorManager::findFood(CircleDecorator* food)
{
	std::vector<CircleDecorator*> vec = { food };
	for (auto &predator : this->_entities)
	{
		((Predator *)predator)->findTarget(vec);
	}
}

PredatorManager &PredatorManager::getInstance()
{
	if (PredatorManager::instance == nullptr)
	{
		PredatorManager::instance = new PredatorManager();
	}
	return *PredatorManager::instance;
}

CircleDecorator *PredatorManager::newEntityInstance(Rectangle<int> areaToAdd)
{
	return new Predator("assets/predatorCircle.png", 30.0f);
}