#include "prey.hpp"

Prey::Prey()
{}

Prey::~Prey()
{}

Prey::Prey(const char *assetName, float radius) :
	NPC(assetName, radius)
{}