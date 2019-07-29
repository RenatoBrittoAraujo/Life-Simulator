#include "foodmanager.hpp"
#include "util.hpp"
#include "life.hpp"
#include "rectangle.hpp"
#include "graphics.hpp"

#include <algorithm>
#include <vector>

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
  if (this->_foods.size() < this->_lowerFoodBound)
  {
    addFood(this->_lowerFoodBound - this->_foods.size());
  }
}

void FoodManager::eatCheck(std::vector<Life*> &foodEaters)
{
  for (auto &food : this->_foods)
  {
    for (auto &foodEater : foodEaters)
    {
      if(foodEater->isInFoodRadius(food))
      {
        foodEater->setNourishment(foodEater->getNourishment() + food->getNutritionalValue());
        delete food;
        food = NULL;
        break;
      }
    }
  }
  Util::clearNullPointers(this->_foods);
}

void FoodManager::collide(std::vector<GameObject*> foodColliders)
{
  for (auto food : this->_foods)
  {
    foodColliders.push_back(food->getCircle());
  }
  for (auto food : this->_foods)
  {
    food->getCircle()->collide(foodColliders);
  }
}

void FoodManager::draw(Point shift)
{
  for (auto food : this->_foods)
  {
    food->draw(shift);
  }
}

void FoodManager::destroy(Rectangle<int> areaToAnalize)
{
  for (auto &food : this->_foods)
  {
    if (areaToAnalize.contains(food->getCircle()->getCenteredPosition()))
    {
      delete food;
      food = nullptr;
    }
  }
  Util::clearNullPointers(this->_foods);
}

void FoodManager::populate(Rectangle<int> areaToAnalize, int numberOfFoods)
{
  if (numberOfFoods == INVALID_AMOUNT)
  {
    numberOfFoods = (int) (this->_foodDensity * areaToAnalize.getArea());
    numberOfFoods = std::min(numberOfFoods, this->_upperFoodBound + (int) this->_foods.size());
    numberOfFoods = std::max(numberOfFoods, this->_lowerFoodBound - (int) this->_foods.size());
  }
  for (int i = 0; i < numberOfFoods; i++)
  {
    Food* food = new Food("assets/food.png", 10.0f);
    food->setPosition(Point(
      Util::randFloat(areaToAnalize.getLeft(), areaToAnalize.getRight()),
      Util::randFloat(areaToAnalize.getTop(), areaToAnalize.getBottom())
    ));
    this->_foods.push_back(food);
  }
}

void FoodManager::reset(Rectangle<int> areaToAnalize)
{
  this->destroy(areaToAnalize);
  this->populate(areaToAnalize);
}

FoodManager& FoodManager::getInstance()
{
  if(FoodManager::instance == NULL)
  {
    FoodManager::instance = new FoodManager();
  }
  return *FoodManager::instance;
}

void FoodManager::addFood(int numberOfNewFoods, Rectangle<int> areaToAdd)
{
  for (int i = 0; i < numberOfNewFoods; i++)
  {
    Food* food = new Food("assets/food.png", 10.0f);
    food->setPosition(Point(
      Util::randFloat(areaToAdd.getLeft(), areaToAdd.getRight()),
      Util::randFloat(areaToAdd.getTop(), areaToAdd.getBottom())
    ));
    this->_foods.push_back(food);
  }
}