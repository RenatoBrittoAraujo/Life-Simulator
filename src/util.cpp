#include "util.hpp"

#include <SDL2/SDL.h>

#include <random>
#include <string>
#include <fstream>
#include <iostream>

namespace GlobalVariables
{
const char *GAME_NAME = "Life Simulator";
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
}

const int Util::getScreenWidth() { return GlobalVariables::SCREEN_WIDTH; }
const int Util::getScreenHeight() { return GlobalVariables::SCREEN_HEIGHT; }
const char* Util::getGameName() { return GlobalVariables::GAME_NAME; }

const int Util::randInt(int lower, int upper)
{
	if (lower > upper)
	{
		throw "randInt(): lower > upper";
	}
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> int_dist(lower, upper);
	return int_dist(mt);
}

const bool Util::fileExists(const std::string &path)
{
	std::ifstream file;
	file.open(path);
	return file.good();
}

const bool Util::fequals(float a, float b)
{
	return fabs(a - b) < 1e-6;
}

const int Util::applyScale(int a, float scale)
{
	return (int)(float(a) * scale);
}

const float Util::applyScale(float a, float scale)
{
	return a * scale;
}

template <typename T>
void Util::permute(std::vector<T> &vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		std::swap(vector[i], vector[randInt(0, vector.size() - 1)]);
	}
}

template void Util::permute<int>(std::vector<int> &);

void Util::logError(std::string errorModule, std::string errorDescription, std::string sdlError)
{
	std::cout << " [ ERROR ] " << errorModule << std::endl;
	std::cout << " ==> " << errorDescription << std::endl;
	if (sdlError != "")
	{
		std::cout << " ==> " << sdlError << std::endl;
	}
}

const void Util::logInfo(std::string info)
{
	std::cout << " [ INFO ] " << info << std::endl;
}