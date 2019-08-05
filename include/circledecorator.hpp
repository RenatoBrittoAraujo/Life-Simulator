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

	void draw(Point shift = Point(0,0));
	virtual void update() = 0;

	Circle& getCircle() { return this->_circle; }

	void addFollower(CircleDecorator* newFollower);
	void removeFollower(CircleDecorator* oldFollower);
	void addFollowing(CircleDecorator* followTarget);
	void setTarget(CircleDecorator* toFollow);
	CircleDecorator* getTarget() const;
	bool isFollowingSomething() const;
	bool hasFollowers() const;

	void collide(std::vector<GameObject*> &objects);
	void collide(std::vector<CircleDecorator *> &objects);

	virtual const std::string type() const { return "CIRCLEDECORATOR"; }

	int getNutritionalValue() const { return (int)(this->_circle.getRadius() * this->_nutritionalValueMultiplier); }

protected:

	float _nutritionalValueMultiplier = 1.0f;

	void init(const char *assetName, float radius);
	Circle _circle;
	std::vector<CircleDecorator*> _followers;
	std::vector<CircleDecorator*> _following;

	CircleDecorator* _target = nullptr;
};

#endif
