#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "point.hpp"
#include "graphics.hpp"

class Segment
{
public:
	Segment();
	~Segment();

	Segment(Point first, Point second);

	/*
		Draws segment to screen
	 */
	void draw(Graphics &graphics, Point shift = Point(0, 0));

	Point getFirst() const { return Point(this->_first); }
	Point getSecond() const { return Point(this->_second); }

	/*
		Multiplies x and y of the points by scaleValue
	 */
	void scale(float scaleValue);

	bool operator<(const Segment other) const
	{
		return this->_first == other.getFirst() ? this->_second < other.getSecond() : this->_first < other.getFirst();
	}

	bool operator==(Segment other)
	{
		return this->_first == other.getFirst() and
					 this->_second == other.getSecond();
	}

private:
	Point _first;
	Point _second;
};

#endif