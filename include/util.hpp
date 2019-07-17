#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

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
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	// static const char* getStringFromDirection(Direction direction)
	// {
	// 	direction == Direction::TOP ? "TOP" :
	// 	direction == Direction::BOTTOM ? "BOTTOM" :
	// 	direction == Direction::LEFT ? "LEFT" :
	// 	direction == Direction::RIGHT ? "RIGHT" :
	// 	"NONE";
	// }
};

#endif