#ifndef FOODMANAGER_HPP
#define FOODMANAGER_HPP

#include "food.hpp"
#include "life.hpp"
#include "rectangle.hpp"
#include "globals.hpp"
#include "entitymanager.hpp"

class FoodManager : public EntityManager
{
public:

  FoodManager();
  ~FoodManager();

  static FoodManager& getInstance();

  void update();
  void collide(std::vector<GameObject*> foodColliders);

	CircleDecorator* newEntityInstance(Rectangle<int> areaToAdd);

private:

	static FoodManager* instance;

};

#endif