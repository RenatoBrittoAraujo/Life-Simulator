#include "spriteobject.hpp"
#include "box.hpp"
#include "graphics.hpp"

#include <string>
#include <vector>
#include <map>

// Public

#include <iostream>

Box::Box(Graphics &graphics, const char *assetName, float width, float height) : 
	SpriteObject(graphics, assetName, width, height)
{}
