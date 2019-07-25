#include "gameobject.hpp"
#include "sprite.hpp"
#include "segment.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "box.hpp"
#include "circle.hpp"
#include "collision.hpp"

GameObject::GameObject()
{}

GameObject::~GameObject()
{
}

void GameObject::update()
{
}

void GameObject::move(Util::Direction direction)
{
}

int GameObject::collide(std::vector<GameObject *> objects)
{
	int collisionNumber = 0;
	for (auto &object : objects)
	{
		if (Collision::handleCollision(this, object))
		{
			collisionNumber++;
		}
	}
	return collisionNumber;
}