#include "spriteobject.hpp"
#include "circle.hpp"
#include "graphics.hpp"

#include <string>
#include <vector>
#include <map>

// Public

Circle::Circle(Graphics &graphics, const char *assetName, float radius) : _radius(radius), 
	SpriteObject(graphics, assetName, radius, radius)
{
}