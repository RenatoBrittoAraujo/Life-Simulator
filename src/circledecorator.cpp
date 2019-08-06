#include "circledecorator.hpp"
#include "npc.hpp"

CircleDecorator::CircleDecorator() 
{}

CircleDecorator::~CircleDecorator()
{}

CircleDecorator::CircleDecorator(const char *assetName, float radius)
{
	this->_circle = Circle(*Graphics::getInstance(), assetName, radius);
}

void CircleDecorator::init(const char *assetName, float radius)
{
	this->_circle = Circle(*Graphics::getInstance(), assetName, radius);
}

Point CircleDecorator::setPosition(const Point newPosition)
{
	this->_circle.setPosition(
		Point(
				newPosition.getX() - this->_circle.getWidth() / 2.0f,
				newPosition.getY() - this->_circle.getHeight() / 2.0f
		)
	);
}

Point CircleDecorator::getPosition() const
{
	return Point(
		this->_circle.getX() + this->_circle.getWidth() / 2.0f,
		this->_circle.getY() + this->_circle.getHeight() / 2.0f
	);
}

float CircleDecorator::getWeight() const { return this->_circle.getWeight(); }
void CircleDecorator::setWeight(const float weight) { this->_circle.setWeight(weight); }

void CircleDecorator::draw(Point shift)
{
	this->_circle.draw(*Graphics::getInstance(), shift);
}

int CircleDecorator::collide(std::vector<GameObject*> &objects)
{
	return this->_circle.collide(objects);
}

int CircleDecorator::collide(GameObject* object)
{
	std::vector<GameObject*> vec = {object};
	return this->_circle.collide(vec);
}