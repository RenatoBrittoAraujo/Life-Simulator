#ifndef UTIL_HPP
#define UTIL_HPP

#include "graphics.hpp"

#include <string>
#include <vector>
#include <limits>

namespace PhysicsConstants
{
const float gravity = 0.0;
const float bounceSpeedFactor = 0.6;
} // namespace PhysicsConstants

class Util
{
public:
	/*
		Returns an integer in the interval [lower,upper]
	 */
	static const int randInt(int lower, int upper);

	/*
		Returns an float in the interval [lower,upper]
	 */
	static const float randFloat(float lower, float upper);

	/*
		Returns true if any file was found in path passed
	 */
	static const bool fileExists(const std::string &path);

	/*
		Returns true if float a and b are less then 10^(-6)
		far apart from each other false otherwise

	 */
	static const bool fequals(float a, float b);

	/*
		returns the scaled value scaled by sprite scale
	 */
	static const int applyScale(int a, float scale);
	static const float applyScale(float a, float scale);

	/*
		Permutes a list randomly
	 */
	template <typename T>
	static void permute(std::vector<T> &vector);

	static void logError(std::string errorModule, std::string errorDescription, std::string sdlError = "");

	static const void logInfo(std::string info);

	static int getScreenHeight();
	static int getScreenWidth();
	const static char* getGameName();

	enum Direction
	{
		NONE = 0,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	static const std::string getStringFromDirection(Direction direction)
	{
		return direction == Direction::TOP ? "TOP" :
		direction == Direction::BOTTOM ? "BOTTOM" :
		direction == Direction::LEFT ? "LEFT" :
		direction == Direction::RIGHT ? "RIGHT" :
		"NONE";
	}

	static const float floatMax()
	{
		return std::numeric_limits<float>::max();
	}

	static void setFullscreenMode(Graphics &graphics);
	static void setWindowedMode(int width = 1280, int height = 720);

private:

	static bool _fullscreen;
	static int _screenWidth;
	static int _screenHeight;

};

#endif