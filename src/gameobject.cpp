#include "gameobject.hpp"
#include "sprite.hpp"
#include "segment.hpp"
#include "point.hpp"
#include "rectangle.hpp"

GameObject::GameObject()
{}

GameObject::~GameObject()
{
}

void GameObject::setSprite(Graphics &graphics, const std::string assetName, Rectangle sourceRect, float targetWidth, float targetHeight)
{
	this->_sprite = new Sprite(graphics, assetName, sourceRect, targetWidth, targetHeight);
}

std::map<std::string, Rectangle> GameObject::images({
	{"npcSquare.png", Rectangle(0.0f, 0.0f, 512.0f, 512.0f)},
	{"playerSquare.png", Rectangle(0.0f, 0.0f, 310.0f, 310.0f)}
});

void GameObject::update()
{
}

void GameObject::move(Util::Direction direction)
{
}

void GameObject::collide(std::vector<GameObject *> objects)
{
}