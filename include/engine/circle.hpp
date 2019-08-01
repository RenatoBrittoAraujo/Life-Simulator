#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "spriteobject.hpp"
#include "graphics.hpp"
#include "util.hpp"

class Circle : public SpriteObject
{
public:

	Circle() {}
	~Circle() {}

	Circle(Graphics &graphics, const char *assetName, float radius);

	/*
		Base class virtuals
	 */
	const GameObjectTypes type() const { return CIRCLE; };

	/*
		Getters and setters
	 */

	float getRadius() const { return this->_radius; }
	void setRadius(const float radius) { 
		this->_radius = radius; 
		setWidth(2.0f * radius); 
		setHeight(2.0f * radius); 
	}

private:

	float _radius;

};

#endif