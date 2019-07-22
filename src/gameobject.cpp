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

void GameObject::setSprite(Graphics &graphics, const std::string assetName, Rectangle sourceRect, float targetWidth, float targetHeight)
{

}

void GameObject::update()
{
}

void GameObject::move(Util::Direction direction)
{
}

void GameObject::collide(std::vector<GameObject *> objects)
{
	for (auto &object : objects)
	{
		Collision::handleCollision(this, object);
	}
}