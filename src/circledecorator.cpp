#include "circledecorator.hpp"
#include "npc.hpp"

void CircleDecorator::addFollower(NPC* newFollower)
{
  this->_followers.push_back(newFollower);
}

void CircleDecorator::removeFollower(NPC* oldFollower)
{
  for (int i = 0; i < this->_followers.size(); i++)
  {
    if(this->_followers[i] == oldFollower)
    {
      this->_followers.erase(this->_followers.begin() + i);
      break;
    }
  }
}