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

	void updateSprite(Graphics &graphics);

	void draw(Graphics &graphics, Point shift = Point(0, 0));
	void update();
	void move(Util::Direction direction);
	virtual const GameObjectTypes type() const { return SPRITEOBJECT; };

	Point getFixedShift() const;

	/*
		Getters and Setters
	 */

	Rectangle<float> getBoundingBox() const
	{
		return Rectangle<float>(this->_x, this->_y, this->_width, this->_height);
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

	float getMovementSpeed() const { return this->_movementSpeed; }
	float getWeight() const { return this->_weight; }
	float getAttritionFactor() const { return this->_attritionFactor; }
	float getSpeedCap() const { return this->_speedCap; }
	void setMovementSpeed(const float movementSpeed) { this->_movementSpeed = movementSpeed; }
	void setWeight(const float weight) { this->_weight = weight; }
	void setAttritionFactor(const float attritionFactor) { this->_attritionFactor = attritionFactor; }
	void setSpeedCap(const float speedCap) { this->_speedCap = speedCap; }

private:

	void setSprite(Graphics &graphics, const std::string assetName, int imageWidth, int imageHeight);
	static std::map<std::string, Rectangle<int>> images;
	Sprite *_sprite = nullptr;

	float _x;
	float _y;
	float _xSpeed;
	float _ySpeed;

	float _width;
	float _height;

	bool _fixed;
	Point _fixedPosition;

	std::string _assetName;

	float _movementSpeed;
	float _weight;
	float _attritionFactor;
	float _speedCap;
};

#endif