#include "food.hpp"
#include "graphics.hpp"

float Food::rotRate = 0.0013f;

Food::Food()
{}

Food::~Food()
{}

Food::Food(float radius) :
	Life("assets/food1.png", radius)
{}

void Food::update()
{
	float oldRot = this->_rot;
	this->_rot = std::min(this->_rot + rotRate * this->_size, 1.0f);
	this->_rot = std::max(this->_rot, 0.0f);
	if ((int)(oldRot * (float)rotLevels) != (int)(this->_rot * (float)rotLevels))
	{
		this->_circle.updateSprite(*Graphics::getInstance(), "assets/food" + std::to_string((int)(this->_rot * (float)rotLevels)) + ".png");
	}
	this->_circle.update();
}