#ifndef FOODMANAGER_HPP
#define FOODMANAGER_HPP

#include "food.hpp"
#include "life.hpp"
#include "rectangle.hpp"
#include "globals.hpp"

class FoodManager
{
public:

  FoodManager();
  ~FoodManager();

  FoodManager(int lowerFoodBound, int upperFoodBound, float foodDensity);

  static FoodManager& getInstance();

  void draw(Point shift);
  void update();
  void eatCheck(std::vector<Life*> &foodEaters);
  void collide(std::vector<GameObject*> foodColliders);
  void reset(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect());
  void populate(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect(), int numberOfNewFoods = INVALID_AMOUNT);
  void destroy(Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect());
  // TODO
  // void addFood(int numberOfNewFoods, Rectangle<int> areaToAnalize = Globals::getInstance().getGameMapRect());

  /*
    Getters and Setters
   */

  void setLowerFoodBound(const int lowerFoodBound) { this->_lowerFoodBound = lowerFoodBound; }
  void setUpperFoodBound(const int upperFoodBound) { this->_upperFoodBound = upperFoodBound; }
  void setFoodDensity(const float foodDensity) { this->_foodDensity = foodDensity; }
  int getLowerFoodBound() const { return this->_lowerFoodBound; }
  int getUpperFoodBound() const { return this->_upperFoodBound; }
  float getFoodDensity() const { return this->_foodDensity; }

private:

  static const int INVALID_AMOUNT = -1;

  static FoodManager* instance;
  std::vector<Food*> _foods;

  float _foodDensity = 0.00001f;
  int _lowerFoodBound = 0;
  int _upperFoodBound = 100;

};

#endif