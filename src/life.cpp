

// void Life::setRandomMovement(Util::Direction direction)
// {
// 	int movementToken = Util::randInt(0, 100);
// 	if (movementToken < 50)
// 	{
// 		this->_randomMovementDirection = Util::Direction::NONE;
// 	}
// 	else if (movementToken < 50 / 4 + 50 or direction == Util::Direction::LEFT)
// 	{
// 		this->_randomMovementDirection = Util::Direction::LEFT;
// 	}
// 	else if (movementToken < 50 / 2 + 50 or direction == Util::Direction::RIGHT)
// 	{
// 		this->_randomMovementDirection = Util::Direction::RIGHT;
// 	}
// 	else if (movementToken < 50 / 2 + 50 / 4 + 50 or direction == Util::Direction::TOP)
// 	{
// 		this->_randomMovementDirection = Util::Direction::TOP;
// 	}
// 	else
// 	{
// 		this->_randomMovementDirection = Util::Direction::BOTTOM;
// 	}
// }

// void Life::moveRandomly()
// {
// 	switch(this->_randomMovementDirection)
// 	{
// 	case Util::Direction::BOTTOM:
// 		this->moveDown();
// 		break;
// 	case Util::Direction::TOP:
// 		this->moveUp();
// 		break;
// 	case Util::Direction::LEFT:
// 		this->moveLeft();
// 		break;
// 	case Util::Direction::RIGHT:
// 		this->moveRight();
// 		break;
// 	default:
// 		break;
// 	}
// }

// const Point Life::getCenteredShift() const
// {
// 	Point position = this->getPosition();
// 	position.setX(position.getX() - (Util::getScreenWidth() / 2.0f - this->_width / 2.0f));
// 	position.setY(position.getY() - (Util::getScreenHeight() / 2.0f - this->_height / 2.0f));
// 	return position;
// }
