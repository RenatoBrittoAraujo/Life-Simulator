#ifndef BOX_HPP
#define BOX_HPP

#include "rectangle.hpp"
#include "point.hpp"
#include "graphics.hpp"
#include "gameobject.hpp"

class Box : public GameObject
{
public:

	Box() {}
	~Box() {}

	Box(Graphics &graphics, const char *assetName, float width, float height = Util::floatMax());

	/*
		Base class virtuals
	 */

	void setSprite(Graphics &graphics, const char *assetName, int imageWidth, int imageHeight);
	void draw(Graphics &graphics, Point shift = Point(0, 0));
	void update();
	void collide(std::vector<GameObject*> objects);
	void move(Util::Direction direction);
	const std::string type() const { return "Box"; };

	/*
		Getters and Setters
	 */

	Rectangle getBoundingBox() const { return Rectangle(this->_x, this->_y, this->_width, this->_height); }
	void setBoundingBox(const Rectangle rect)
	{
		this->_x = rect.getLeft();
		this->_y = rect.getTop();
		this->_height = rect.getHeight();
		this->_width = rect.getWidth();
	}

	Point getPosition() const { return Point(this->_x, this->_y); }
	void setPosition(const Point position)
	{
		this->_x = position.getX();
		this->_y = position.getY();
	}

	float getX() const { return this->_x; }
	float getY() const { return this->_y; }
	void setX(const float x) { this->_x = x; }
	void setY(const float y) { this->_y = y; }

	float getWidth() const { return this->_width; };
	float getHeight() const { return this->_height; };
	void setWidth(const float width) { this->_width = width; };
	void setHeight(const float height) { this->_height = height; };

	float getXSpeed() const { return this->_xSpeed; }
	float getYSpeed() const { return this->_ySpeed; }
	void setXSpeed(const float xSpeed) { this->_xSpeed = xSpeed; }
	void setYSpeed(const float ySpeed) { this->_ySpeed = ySpeed; }

private:

	float _x, _y;
	float _height, _width;

	const char *_assetName;

	float _xSpeed;
	float _ySpeed;

};

#endif