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
	for (auto &food : this->_entities)
  {
    food->update();
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

CircleDecorator *FoodManager::newEntityInstance(Rectangle<int> areaToAdd)
{
	return new Food("assets/food.png", 10.0f);
}