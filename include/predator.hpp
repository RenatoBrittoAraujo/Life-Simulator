#ifndef PREDATOR_HPP
#define PREDATOR_HPP

#include "npc.hpp"

class Predator : public NPC
{
public:

  virtual const std::string type() { return "PREDATOR"; }

private:

};

#endif