#include "box.hpp"
#include "life.hpp"

Life::Life()
{
	this->_box.setCentered(false);
}

Life::~Life()
{
}

Life::Life(Graphics &graphics, const char *assetName, float width, float height)
{
	this->_box = Box(graphics, assetName, width, height);
	this->_box.setCentered(false);
}

void Life::draw(Graphics &graphics)
{
	this->_box.draw(graphics);
}

void Life::update()
{
	this->_box.update();
}