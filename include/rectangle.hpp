#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "util.hpp"
#include <SDL2/SDL.h>

#include <algorithm>

class Rectangle
{
public:
	Rectangle(){};

	Rectangle(float x, float y, float width, float height) : 
		_x(x),
		_y(y),
		_width(width),
		_height(height)
	{}

	const float getCenterX() const { return this->_x + this->_width / 2; }
	const float getCenterY() const { return this->_y + this->_height / 2; }

	const float getLeft() const { return this->_x; }
	const float getRight() const { return this->_x + this->_width; }
	const float getTop() const { return this->_y; }
	const float getBottom() const { return this->_y + this->_height; }

	const float getHeight() const { return this->_height; }
	const float getWidth() const { return this->_width; }

	bool operator == (const Rectangle &other) const
	{
		return Util::fequals(getBottom(), other.getBottom()) and
					 Util::fequals(getTop(), other.getTop()) and
					 Util::fequals(getLeft(), other.getLeft()) and
					 Util::fequals(getRight(), other.getRight());
	}

	const float getSide(const Util::Direction side) const
	{
		return side == Util::Direction::LEFT ? this->getLeft() : side == Util::Direction::RIGHT ? this->getRight() : side == Util::Direction::TOP ? this->getTop() : side == Util::Direction::BOTTOM ? this->getBottom() : Util::Direction::NONE;
	}

	const bool collidesWith(const Rectangle &other) const
	{
		return this->getRight() >= other.getLeft() and
					 this->getLeft() <= other.getRight() and
					 this->getTop() <= other.getBottom() and
					 this->getBottom() >= other.getTop();
	}

	const Util::Direction collisionSide(const Rectangle &other) const
	{
		std::vector<std::pair<float, Util::Direction>> distances;
		distances.push_back({ fabs(getLeft() - other.getRight()), Util::Direction::LEFT });
		distances.push_back({fabs(getRight() - other.getLeft()), Util::Direction::RIGHT});
		distances.push_back({fabs(getTop() - other.getBottom()), Util::Direction::TOP});
		distances.push_back({fabs(getBottom() - other.getTop()), Util::Direction::BOTTOM});
		sort(distances.begin(), distances.end(), [&](std::pair<float, Util::Direction> a, std::pair<float, Util::Direction> b) {
			return a.first < b.first;
		});
		return distances[0].second;
	}

	const float collisionLength(const Rectangle &other) const
	{
		std::vector<float> distances;
		distances.push_back(fabs(getLeft() - other.getRight()));
		distances.push_back(fabs(getRight() - other.getLeft()));
		distances.push_back(fabs(getTop() - other.getBottom()));
		distances.push_back(fabs(getBottom() - other.getTop()));
		sort(distances.begin(), distances.end());
		return distances[0];
	}

	const bool isValid() const
	{
		return this->_x >= 0 and this->_y >= 0 and this->_width >= 0 and this->_height >= 0;
	}

	const inline Rectangle getRect() const { return *this; }

	void scale(const float scaleFactor)
	{
		this->_width *= scaleFactor;
		this->_height *= scaleFactor;
	}

	/*
		Fits into a specficied width and height but without exceeding it. If fit is not perfect, fit as most as possible without exceeding
	 */
	void fit(const float width, const float height)
	{
		float rel = this->_width / this->_height;
		float newHeight = width / rel;
		float newWidth = rel * height;
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

private:
	float _x, _y, _width, _height;
};

#endif