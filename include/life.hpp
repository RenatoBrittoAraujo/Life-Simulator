#ifndef LIFE_HPP
#define LIFE_HPP

#include "util.hpp"
#include "point.hpp"
#include "segment.hpp"
#include "graphics.hpp"
#include "rectangle.hpp"
#include "sprite.hpp"

#include <vector>

class Life
{
public:
	Life();
	~Life();

	Life(Graphics &graphics, const char *assetName, const int imageWidth, int imageHeight);

	/*
		Loads image of sprite
	 */
	void loadSprite(Graphics &graphics, const char *assetName, const int imageWidth, int imageHeight, float scale);

	/*
		Draws life to renderer
	 */
	void draw(Graphics &graphics, Point shift = Point(0,0));

	/*
		Returns relative shift every object has to do in relation to centered object's position
	 */
	const Point getCenteredShift() const;

	/*
		Updates attributes
	 */
	void update();

	/*
		Changes acceleration
	 */
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void setRandomMovement(Util::Direction direction = Util::Direction::NONE);

	/*
		Checks if life is colliding with some segment of segments
	 */
	void collisionCheck(std::vector<Segment> segments, std::vector<Life *> lives);


	// Getters and Setters

	void setCentered(const bool centered) { this->_centered = centered; }
	Point getPosition() const { return Point(this->_x, this->_y); }
	Rectangle getBoundingBox() const { return Rectangle(this->_x, this->_y, this->_width, this->_height); }
	void setPosition(const Point position) { this->_x = position.getX(); this->_y = position.getY(); }
	float getX() const { return this->_x; }
	float getY() const { return this->_y; }
	void setX(const float x) { this->_x =  x; }
	void setY(const float y) { this->_y = y; }
	float getXSpeed() const { return this->_xSpeed; }
	float getYSpeed() const { return this->_ySpeed; }
	void setXSpeed(const float xSpeed) { this->_xSpeed = xSpeed; }
	void setYSpeed(const float ySpeed) { this->_ySpeed = ySpeed; }

private:

	Sprite *_sprite;

	float _x, _y;
	float _height, _width;

	float _xSpeed = 0;
	float _ySpeed = 0;

	bool _centered = false;

	void moveRandomly();

	Util::Direction _randomMovementDirection = Util::Direction::NONE;

	/*
		Handles collisions with a specific segment
	 */
	void handleSegmentCollision(Segment segment);

	/*
		Handle collisions with other lifes
	 */
	void handleLifeCollision(Life *life);

};

#endif