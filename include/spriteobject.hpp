#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP

#include "graphics.hpp"
#include "util.hpp"
#include "point.hpp"
#include "vector2D.hpp"
#include "gameobject.hpp"

class SpriteObject : public GameObject
{
public:

	SpriteObject();
	~SpriteObject();

	SpriteObject(Graphics &graphics, const std::string assetName, float width, float height);

	virtual void setSprite(Graphics &graphics, const std::string assetName, int imageWidth, int imageHeight);
	virtual void draw(Graphics &graphics, Point shift = Point(0, 0));
	virtual void update();
	virtual void move(Util::Direction direction);
	virtual const GameObjectTypes type() const { return SPRITEOBJECT; };

	Point getFixedShift() const;

	/*
		Getters and Setters
	 */

			Rectangle
			getBoundingBox() const
	{
		return Rectangle(this->_x, this->_y, this->_width, this->_height);
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

	Vector2D getSpeed() const { return Vector2D(this->_xSpeed, this->_ySpeed); }
	void setSpeed(const Vector2D speed) { this->_xSpeed = speed.getX(); this->_ySpeed = speed.getY(); }

	void setFixed(const bool fixed) { this->_fixed = fixed; }
	bool getFixed() const { return this->_fixed; }
	void setFixedPosition(const Point fixedPosition) { this->_fixedPosition = fixedPosition; }
	Point getFixedPosition() const { return this->_fixedPosition; }

private:

	static std::map<std::string, Rectangle> images;
	Sprite *_sprite = nullptr;

	float _x;
	float _y;
	float _xSpeed;
	float _ySpeed;

	float _width;
	float _height;

	bool _fixed;
	Point _fixedPosition;

};

#endif