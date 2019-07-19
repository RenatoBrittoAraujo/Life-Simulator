#include "gameobject.hpp"
#include "sprite.hpp"
#include "segment.hpp"
#include "point.hpp"
#include "rectangle.hpp"

GameObject::GameObject()
{}

GameObject::~GameObject()
{
	delete this->_sprite;
}

void GameObject::setSprite(Graphics &graphics, const std::string assetName, Rectangle sourceRect, float targetWidth, float targetHeight)
{
	this->_sprite = new Sprite(graphics, assetName, sourceRect, targetWidth, targetHeight);
}

std::map<std::string, Rectangle> GameObject::images({
	{"npcSquare.png", Rectangle(0, 0, 512, 512)},
	{"playerSquare.png", Rectangle(0, 0, 310, 310)}
});

void update()
{

}

void move(Util::Direction direction)
{

}

void collide(std::vector<GameObject *> objects)
{

}