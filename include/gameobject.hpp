#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "point.hpp"
#include "graphics.hpp"
#include "rectangle.hpp"
#include "sprite.hpp"

#include <string>

/*
	A GameObject is any object that APPEARS ON SCREEN.
 */

enum GameObjectTypes
{
	GAMEOBJECT,
	SPRITEOBJECT,
	BOX,
	CIRCLE,
	SEGMENT
};

class GameObject
{
public:

	GameObject();
	~GameObject();

	// ATTENTION: Virtual classes ahead, any class that is drawable to screen should take in account these considerations:
	// Does it move? How does it move?
	// Does it collides? How does it's collision work?
	// Does it update? How does it update?

	/*
		Loads image as sprite
	 */
	virtual void setSprite(Graphics &graphics, const std::string assetName, Rectangle sourceRect, float targetWidth, float targetHeight);

	/*
		Draws GameObject to renderer
	 */
	virtual void draw(Graphics &graphics, Point shift = Point(0, 0)) = 0;

	/*
		Moves GameObject to especified direction
	 */
	virtual void move(Util::Direction direction);

	/*
		Handles collisions with other GameObjects
	 */
	virtual void collide(std::vector<GameObject*> objects);

	/*
		Updates GameObjects attributes
	 */
	virtual void update();

	virtual const GameObjectTypes type() const { return GAMEOBJECT; };

	/*
	 Basic getters and setters
	 */

	void setMovingObject(const bool movingObject) { this->_moves = movingObject; }
	bool moves() const { return this->_moves; }

	void setCollidingObject(const bool collidingObject) { this->_collides = collidingObject; }
	bool collides() const { return this->_collides; }

	void setUpdatingObject(const bool updatingObject) { this->_updates = updatingObject; }
	bool updates() const { return this->_updates; }

private:

	bool _moves;
	bool _collides;
	bool _updates;

};

#endif