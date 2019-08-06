#ifndef CIRCLEDECORATOR_HPP
#define CIRCLEDECORATOR_HPP

#include "circle.hpp"

class NPC;

class CircleDecorator {

public:

	CircleDecorator();

	~CircleDecorator();

	CircleDecorator(const char *assetName, float radius);

	Point setPosition(const Point newPosition);
	Point getPosition() const;

	float getWeight() const;
	void setWeight(const float weight);

	float getRadius() const { return this->_circle.getRadius(); }

	virtual void draw(Point shift = Point(0,0));
	virtual void update() = 0;

	Circle& getCircle() { return this->_circle; }

	int collide(std::vector<GameObject*> &objects);
	int collide(std::vector<CircleDecorator *> &objects);
	int collide(GameObject* object);

	virtual const std::string type() const { return "CIRCLEDECORATOR"; }

protected:

	void init(const char *assetName, float radius);
	Circle _circle;
};

#endif
