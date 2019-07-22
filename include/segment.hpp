#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "point.hpp"
#include "graphics.hpp"
#include "gameobject.hpp"

class Segment : public GameObject
{
public:
	Segment();
	~Segment();

	Segment(Point first, Point second);

	/*
		Draws segment to screen
	 */
	void draw(Graphics &graphics, Point shift = Point(0, 0));

	void update();
	void move(Util::Direction direction);
	const GameObjectTypes type() const { return SEGMENT; }

	Point getFirst() const { return Point(this->_first); }
	Point getSecond() const { return Point(this->_second); }

	bool operator<(const Segment other) const
	{
		return this->_first == other.getFirst() ? this->_second < other.getSecond() : this->_first < other.getFirst();
	}

	bool operator==(Segment other)
	{
		return this->_first == other.getFirst() and
					this->_second == other.getSecond();
	}

	void setColor(const Color color) { this->_renderColor = color; }
	Color getColor() const { return this->_renderColor; }

private:

	Point _first;
	Point _second;

	Color _renderColor = Color::black();
};

#endif