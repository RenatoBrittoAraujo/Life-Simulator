#ifndef PREY_HPP
#define PREY_HPP

#include "npc.hpp"

class Prey : public NPC
{
public:

  virtual const std::string type() { return "PREY"; }

private:

};

#endif