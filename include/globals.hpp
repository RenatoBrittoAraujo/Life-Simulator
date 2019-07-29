#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "rectangle.hpp"
#include "graphics.hpp"

class Globals
{
public:

  Globals() {}
  ~Globals() {}

  static Globals& getInstance()
  {
    if(_instance == nullptr)
    {
      throw "Globals instance null";
    }
    return *_instance;
  }

  /*
    Getters and Setters
   */

  void setScreenWidth(const int screenWidth) { this->_screenWidth = screenWidth; }
  int getScreenWidth() const { return this->_screenWidth; }
  void setScreenHeight(const int screenHeight) { this->_screenHeight = screenHeight; }
  int getScreenHeight() const { return this->_screenHeight; }

  void setGameMapWidth(const int gameMapWidth) { this->_gameMapWidth = gameMapWidth; }
  int getGameMapWidth() const { return this->_gameMapWidth; }
  void setGameMapHeigth(const int gameMapHeight) { this->_gameMapHeight = gameMapHeight; }
  int getGameMapHeight() const { return this->_gameMapHeight; }

  Rectangle<int> getGameMapRect() const { return Rectangle<int>(0, 0, this->_gameMapWidth, this->_gameMapHeight); }

private:

  static Globals* _instance;

  int _screenWidth;
  int _screenHeight;

  int _gameMapWidth;
  int _gameMapHeight;

};

#endif