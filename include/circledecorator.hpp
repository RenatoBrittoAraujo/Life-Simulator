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

	float getRadius() const { return this->_circle->getRadius(); }

	void draw(Point shift = Point(0,0));

	Circle& getCircle() { return *this->_circle; }

	void addFollower(NPC* newFollower);
	void removeFollower(NPC* oldFollower);

	virtual const std::string type() const { return "CIRCLEDECORATOR"; }

protected:

	Circle *_circle;

	std::vector<NPC*> _followers;

};

#endif
