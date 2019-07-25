#ifndef FONTOBJECT_HPP
#define FONTOBJECT_HPP

#include "gameobject.hpp"
#include "font.hpp"
#include "graphics.hpp"
#include "rectangle.hpp"

#include <SDL2/SDL.h>
#include <string>

class FontObject : public GameObject
{
public:
	FontObject();
	~FontObject();

	FontObject(Graphics &graphics, float width, float height, std::string text);
	FontObject(float width, float height);

	void update(Graphics &graphics, const std::string text);

	void draw(Graphics &graphics, Point shift = Point(0, 0));

	/*
		Getters and setters
	 */

	Rectangle<int> getBoundingBox() const { return Rectangle<int>(this->_x, this->_y, this->_width, this->_height); }
	void setPosition(const Point pos) { this->_x = pos.getX(); this->_y = pos.getY(); }
	Point getPosition() const { return Point(this->_x, this->_y); }
	void setX(const int x) { this->_x = x; }
	void setY(const int y) { this->_y = y; }
	void setWidth(const int width) { this->_width = width; }
	void setHeight(const int height) { this->_height = height; }
	float getX() const { return this->_x; }
	float getY() const { return this->_y; }
	float getWidth() const { return this->_width; }
	float getHeight() const { return this->_height; }

	int getFontSize() const { return this->_fontSize; }
	void setFontSize(const int fontSize) { this->_fontSize = fontSize; }
	Color getColor() const { return this->_fontColor; }
	void setColor(const Color color) { this->_fontColor = color; }
	std::string getFontPath() const { return this->_fontPath; }
	void setFontPath(const std::string path) { this->_fontPath = path; }

private:

	Font _font;

	float _x = 0;
	float _y = 0;
	float _width = 500;
	float _height = 100;
	int _fontSize = 300;
	Color _fontColor = Color::black();
	std::string _fontPath = "assets/bebasneue.ttf";
	std::string _text = "";

};

#endif