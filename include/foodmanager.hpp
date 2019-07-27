#ifndef FOODMANAGER_HPP
#define FOODMANAGER_HPP

#include "food.hpp"
#include "life.hpp"

class FoodManager
{
public:

  FoodManager();
  ~FoodManager();

  FoodManager(int lowerFoodBound, int upperFoodBound, float foodDensity);

  static FoodManager& getInstance();

  void draw(Graphics &graphics);
  void eatCheck(std::vector<Life*> foodEaters);
  void update();
  void reset(int gameWidth, int gameHeight);
  void populate(int gameWidth, int gameHeight);
  void destroy();

  /*
    Getters and Setters
   */

  void setLowerFoodBound(const int lowerFoodBound) {}
  void setUpperFoodBound(const int upperFoodBound) {}
  void setFoodDensity(const float foodDensity) {}
  int getLowerFoodBound() const { return this->_lowerFoodBound; }
  int getUpperFoodBound() const { return this->_upperFoodBound; }
  float getFoodDensity() const { return this->_foodDensity; }

private:

  static FoodManager* instance;
  std::vector<Food*> _foods;

  float _foodDensity = 0.1;
  int _lowerFoodBound = 0;
  int _upperFoodBound = 100;

};

#endif