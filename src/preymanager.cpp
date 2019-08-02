#include "preymanager.hpp"
#include "prey.hpp"

PreyManager *PreyManager::instance = nullptr;

PreyManager::PreyManager()
{
}

PreyManager::~PreyManager()
{
}

void PreyManager::update()
{
	for (auto &prey : this->_entities)
	{
		prey->update();
	}
	if (this->_entities.size() < this->_lowerEntityBound)
	{
		addEntity(this->_lowerEntityBound - this->_entities.size());
	}
}

void PreyManager::findFood(std::vector<CircleDecorator*> foods)
{
	for (auto &prey : this->_entities)
	{
		((Prey*) prey)->findTarget(foods);
	}
}

PreyManager &PreyManager::getInstance()
{
	if (PreyManager::instance == nullptr)
	{
		PreyManager::instance = new PreyManager();
	}
	return *PreyManager::instance;
}

CircleDecorator *PreyManager::newEntityInstance(Rectangle<int> areaToAdd)
{
	return new Prey("assets/preyCircle.png", 20.0f);
}