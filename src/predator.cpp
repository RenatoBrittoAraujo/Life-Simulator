#include "predator.hpp"

Predator::Predator()
{}

Predator::~Predator()
{}

Predator::Predator(const char *assetName, float radius) : NPC(assetName, radius)
{}