#include "box.hpp"
#include "life.hpp"

Life::Life()
{
}

Life::~Life()
{
}

Life::Life(Graphics &graphics, const char *assetName, float width, float height)
{
	this->_box = Box(graphics, assetName, width, height);
}

void Life::draw(Graphics &graphics)
{
	this->_box.draw(graphics);
}

void Life::update()
{
	this->_box.update();
}