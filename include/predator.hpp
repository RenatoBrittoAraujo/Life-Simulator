#ifndef PREDATOR_HPP
#define PREDATOR_HPP

#include "npc.hpp"

class Predator : public NPC
{

	Predator();
	~Predator();

	Predator(const char *assetName, float radius);

	virtual const std::string type() { return "PREDATOR"; }

private:

};

#endif