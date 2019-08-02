#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "util.hpp"
#include "point.hpp"
#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class Rectangle
{
public:
	Rectangle(){};

	Rectangle(T x, T y, T width, T height) : 
		_x(x),
		_y(y),
		_width(width),
		_height(height)
	{}

	Rectangle(SDL_Rect &rect) :
		_x(rect.x),
		_y(rect.y),
		_width(rect.w),
		_height(rect.h)
	{}

	T getCenterX() const { return this->_x + this->_width / 2; }
	T getCenterY() const { return this->_y + this->_height / 2; }

	T getLeft() const { return this->_x; }
	T getRight() const { return this->_x + this->_width; }
	T getTop() const { return this->_y; }
	T getBottom() const { return this->_y + this->_height; }

	T getHeight() const { return this->_height; }
	T getWidth() const { return this->_width; }

	T getArea() const { return this->_width * this->_height; }

	bool operator == (const Rectangle &other) const
	{
		return Util::fequals(getBottom(), other.getBottom()) and
					 Util::fequals(getTop(), other.getTop()) and
					 Util::fequals(getLeft(), other.getLeft()) and
					 Util::fequals(getRight(), other.getRight());
	}

	const T getSide(const Util::Direction side) const
	{
		return side == Util::Direction::LEFT ? this->getLeft() : side == Util::Direction::RIGHT ? this->getRight() : side == Util::Direction::TOP ? this->getTop() : side == Util::Direction::BOTTOM ? this->getBottom() : Util::Direction::NONE;
	}

	bool collidesWith(const Rectangle &other) const
	{
		return this->getRight() >= other.getLeft() and
					 this->getLeft() <= other.getRight() and
					 this->getTop() <= other.getBottom() and
					 this->getBottom() >= other.getTop();
	}

	bool contains(const Point &point) const
	{
		return 	this->getLeft() <= point.getX() and
						this->getRight() >= point.getX() and
						this->getTop() <= point.getY() and
						this->getBottom() >= point.getX();
	}

	Util::Direction collisionSide(const Rectangle &other) const
	{
		std::vector<std::pair<T, Util::Direction>> distances;
		distances.push_back({ fabs(getLeft() - other.getRight()), Util::Direction::LEFT });
		distances.push_back({fabs(getRight() - other.getLeft()), Util::Direction::RIGHT});
		distances.push_back({fabs(getTop() - other.getBottom()), Util::Direction::TOP});
		distances.push_back({fabs(getBottom() - other.getTop()), Util::Direction::BOTTOM});
		sort(distances.begin(), distances.end(), [&](std::pair<T, Util::Direction> a, std::pair<T, Util::Direction> b) {
			return a.first < b.first;
		});
		return distances[0].second;
	}

	T collisionLength(const Rectangle &other) const
	{
		std::vector<T> distances;
		distances.push_back(fabs(getLeft() - other.getRight()));
		distances.push_back(fabs(getRight() - other.getLeft()));
		distances.push_back(fabs(getTop() - other.getBottom()));
		distances.push_back(fabs(getBottom() - other.getTop()));
		sort(distances.begin(), distances.end());
		return distances[0];
	}

	bool isValid() const
	{
		return this->_x >= 0 and this->_y >= 0 and this->_width >= 0 and this->_height >= 0;
	}

	inline Rectangle getRect() const { return *this; }

	void scale(const T scaleFactor)
	{
		this->_width *= scaleFactor;
		this->_height *= scaleFactor;
	}

	/*
		Fits into a specficied width and height but without exceeding it. If fit is not perfect, fit as most as possible without exceeding
	 */
	void fit(T width, T height)
	{
		T rel = this->_width / this->_height;
		T newHeight = width / rel;
		T newWidth = rel * height;
		if(newHeight > height)
		{
			this->_width = newWidth;
			this->_height = height;
		}
		else
		{
			this->_height = newHeight;
			this->_width = width;
		}
	}

	SDL_Rect toSDLRect()
	{
		SDL_Rect newRect;
		newRect.x = this->_x;
		newRect.y = this->_y;
		newRect.w = this->_width;
		newRect.h = this->_height;
		return newRect;
	}

	void print()
	{
		std::cout << "RECT X = " << getLeft() << " WIDTH = " << getRight() - getLeft() << " Y = " << getTop() << " HEIGHT = " << getBottom() - getTop() << std::endl;
	}

private:
	T _x, _y, _width, _height;
};

#endif