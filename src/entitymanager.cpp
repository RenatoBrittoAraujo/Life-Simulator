#include "entitymanager.hpp"
#include "util.hpp"
#include "life.hpp"
#include "rectangle.hpp"
#include "graphics.hpp"
#include "npc.hpp"

#include <algorithm>
#include <vector>

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

EntityManager::EntityManager(int lowerEntityBound, int upperEntityBound, float entityDensity) : 
_lowerEntityBound(lowerEntityBound), _upperEntityBound(upperEntityBound), _entityDensity(entityDensity)
{}

void EntityManager::update()
{
	for (auto &entity : this->_entities)
	{
		entity->update();
	}
	// if (this->_entities.size() < this->_lowerEntityBound)
	// {
	// 	addEntity(this->_lowerEntityBound - this->_entities.size());
	// }
}

void EntityManager::eatCheck(std::vector<Life *> &entityEaters)
{
	for (int entityIndex = 0; entityIndex < this->_entities.size(); entityIndex++)
	{
		CircleDecorator *entity = this->_entities[entityIndex];
		for (auto &entityEater : entityEaters)
		{
			if (entityEater->targetInRadius(entity))
			{
				entityEater->setNourishment(entityEater->getNourishment() + entity->getNutritionalValue());
				if (entityEater->type() == "NPC")
				{
					((NPC *)entityEater)->setTarget(nullptr);
				}
				removeEntity(entityIndex);
				break;
			}
		}
	}
}

void EntityManager::collide(std::vector<GameObject *> entityColliders)
{
	for (auto entity : this->_entities)
	{
		entityColliders.push_back(&entity->getCircle());
	}
	for (auto entity : this->_entities)
	{
		entity->getCircle().collide(entityColliders);
	}
}

void EntityManager::draw(Point shift)
{
	for (int index = 0; index < this->_entities.size(); index++)
	{
		this->_entities[index]->draw(shift);
	}
}

void EntityManager::destroy(Rectangle<int> areaToAnalize)
{
	for (int entityIndex = 0; entityIndex < this->_entities.size(); entityIndex++)
	{
		if (areaToAnalize.contains(this->_entities.at(entityIndex)->getCircle().getCenteredPosition()))
		{
			removeEntity(entityIndex);
		}
	}
}

void EntityManager::populate(Rectangle<int> areaToAnalize, int numberOfEntitys)
{
	if (numberOfEntitys == INVALID_AMOUNT)
	{
		numberOfEntitys = (int)(this->_entityDensity * areaToAnalize.getArea());
		numberOfEntitys = std::min(numberOfEntitys, this->_upperEntityBound + (int)this->_entities.size());
		numberOfEntitys = std::max(numberOfEntitys, this->_lowerEntityBound - (int)this->_entities.size());
	}
	this->addEntity(numberOfEntitys, areaToAnalize);
}

void EntityManager::reset(Rectangle<int> areaToAnalize)
{
	this->destroy(areaToAnalize);
	this->populate(areaToAnalize);
}

void EntityManager::addEntity(int numberOfNewEntitys, Rectangle<int> areaToAdd)
{
	for (int i = 0; i < numberOfNewEntitys; i++)
	{
		CircleDecorator *entity = newEntityInstance(areaToAdd);
		entity->setPosition(
				Point(
						Util::randFloat(areaToAdd.getLeft(), areaToAdd.getRight()),
						Util::randFloat(areaToAdd.getTop(), areaToAdd.getBottom())));
		storeEntity(entity);
	}
}

void EntityManager::storeEntity(CircleDecorator *entity)
{
	this->_entities.push_back(entity);
}

void EntityManager::removeEntity(int index)
{
	delete this->_entities[index];
	this->_entities.erase(this->_entities.begin() + index);
}