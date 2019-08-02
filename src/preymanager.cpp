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

void PreyManager::collide(std::vector<GameObject *> preyColliders)
{
	for (auto &prey : this->_entities)
	{
		preyColliders.push_back(&prey->getCircle());
	}
	for (auto &prey : this->_entities)
	{
		prey->getCircle().collide(preyColliders);
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
	Prey *prey = new Prey("preyCircle/food.png", 10.0f);
	prey->setPosition(
		Point(
			Util::randFloat(areaToAdd.getLeft(), areaToAdd.getRight()),
			Util::randFloat(areaToAdd.getTop(), areaToAdd.getBottom())
		)
	);
	return prey;
}