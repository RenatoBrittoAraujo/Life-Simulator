#include "foodmanager.hpp"

FoodManager* FoodManager::instance = nullptr;

FoodManager::FoodManager()
{}

FoodManager::~FoodManager()
{}

FoodManager::FoodManager(int lowerFoodBound, int upperFoodBound, float foodDensity) :
  _lowerFoodBound(lowerFoodBound), _upperFoodBound(upperFoodBound), _foodDensity(foodDensity)
{}

void FoodManager::update()
{
  for (auto food : this->_foods)
  {
    food->update();
  }
}

void FoodManager::eatCheck(std::vector<Life*> foodEaters)
{

}

void FoodManager::draw(Graphics &graphics)
{
  for (auto food : this->_foods)
  {
    food->draw(graphics);
  }
}

void FoodManager::destroy()
{
  for (auto food : this->_foods)
  {
    delete food;
  }
  this->_foods.clear();
}

void FoodManager::populate(int gameWidth, int gameHeight)
{

}

void FoodManager::reset(int gameWidth, int gameHeight)
{
  this->destroy();
  this->populate(gameWidth, gameHeight);
}

FoodManager& FoodManager::getInstance()
{
  if(FoodManager::instance == NULL)
  {
    FoodManager::instance = new FoodManager();
  }
  return *FoodManager::instance;
}