#include "Goal.h"

void Goal::releaseGoal()
{
	this->_ActionUser = NULL;
	this->_Map = NULL;

	this->targetX = this->targetY = -1;
}