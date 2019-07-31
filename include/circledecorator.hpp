#ifndef CIRCLEDECORATOR_HPP
#define CIRCLEDECORATOR_HPP

#include "circle.hpp"

class NPC;

class CircleDecorator {

public:

	CircleDecorator() {}
	
	~CircleDecorator() {
		if (this->_circle != nullptr)
		{
				// delete this->_circle;
		}
	}

	CircleDecorator(Graphics &graphics, const char *assetName, float radius) :
		_circle(new Circle(graphics, assetName, radius))
	{}

	Point getPosition() { return this->_circle->getCenteredPosition(); }

	Point setPosition(const Point newPosition) { 
		this->_circle->setPosition(
			Point(
				newPosition.getX() - this->_circle->getWidth() / 2.0f,
				newPosition.getY() - this->_circle->getHeight() / 2.0f
			)
		); 
	}

	Circle& getCircle() { return *this->_circle; }

	void addFollower(NPC* newFollower);
	void removeFollower(NPC* oldFollower);

	virtual const std::string type() = 0;

protected:

	Circle *_circle;

	std::vector<NPC*> _followers;

};

#endif