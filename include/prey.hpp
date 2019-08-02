#ifndef PREY_HPP
#define PREY_HPP

#include "npc.hpp"

class Prey : public NPC
{
public:

	Prey();
	~Prey();

	Prey(const char* assetName, float radius);

  virtual const std::string type() { return "PREY"; }

private:

};

#endif