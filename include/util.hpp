#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include <limits>

namespace PhysicsConstants
{
const float gravity = 0.00;
const float bounceSpeedFactor = 0.8;
} // namespace PhysicsConstants

namespace MovementConstants
{
const float speedCap = 100.0;
const float movementAcceleration = 0.9;
const float attritionFactor = 0.95;
}

class Util
{
public:
	/*
		Returns an integer int the interval [lower,upper]
		Throws exception if lower > upper
	 */
	static const int randInt(int lower, int upper);

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

	const static int getScreenHeight();
	const static int getScreenWidth();
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
};

#endif