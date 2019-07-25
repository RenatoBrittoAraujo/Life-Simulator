#ifndef BOX_HPP
#define BOX_HPP

#include "rectangle.hpp"
#include "point.hpp"
#include "graphics.hpp"
#include "spriteobject.hpp"

class Box : public SpriteObject
{
public:

	Box() {}
	~Box() {}

	Box(Graphics &graphics, const char *assetName, float width, float height);

	const GameObjectTypes type() const { return BOX; };

private:

};

#endif