#include "foodmanager.hpp"
#include "util.hpp"
#include "life.hpp"
#include "rectangle.hpp"
#include "graphics.hpp"
#include "npc.hpp"

#include <algorithm>
#include <vector>

FoodManager* FoodManager::instance = nullptr;

FoodManager::FoodManager()
{}

FoodManager::~FoodManager()
{}

void FoodManager::update()
{
	for (int i = 0; i < this->_entities.size(); i++)
  {
		Food* food = (Food*) this->_entities[i];
    food->update();
		if (((Food*) food)->getRot() >= 1.0f)
		{
			removeEntity(i);
		}
  }
  if (this->_entities.size() < this->_lowerEntityBound)
  {
    addEntity(this->_lowerEntityBound - this->_entities.size());
  }
}

FoodManager& FoodManager::getInstance()
{
  if(FoodManager::instance == nullptr)
  {
    FoodManager::instance = new FoodManager();
  }
  return *FoodManager::instance;
}

Life *FoodManager::newEntityInstance(Rectangle<int> areaToAdd)
{
	return new Food(10.0f);
}