#include "box.hpp"
#include "life.hpp"
#include "circle.hpp"

Life::Life()
{
}

Life::~Life()
{
}

Life::Life(Graphics &graphics, const char *assetName, float width, float height)
{
	this->_box = Circle(graphics, assetName, (width + height) / 2.0f);
}

void Life::draw(Graphics &graphics)
{
	this->_box.draw(graphics);
}

void Life::update()
{
	this->_box.update();
}