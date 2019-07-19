#ifndef LIFE_HPP
#define LIFE_HPP

#include "box.hpp"

class Life
{
public:

	Life();
	~Life();

	Life(Graphics &graphics, const char *assetName, float width, float height);

	virtual void draw(Graphics &graphics);
	virtual void update();

	Box &getBox() { return _box; }

protected:

	Box _box;

};

#endif