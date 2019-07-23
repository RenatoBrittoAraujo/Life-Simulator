#ifndef LIFE_HPP
#define LIFE_HPP

#include "box.hpp"
#include "circle.hpp"

class Life
{
public:

	Life();
	~Life();

	Life(Graphics &graphics, const char *assetName, float width, float height);

	virtual void draw(Graphics &graphics);
	virtual void update();

	Circle &getBox() { return _box; }

protected:

	Circle _box;

};

#endif