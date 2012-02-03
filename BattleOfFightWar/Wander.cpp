#include "Wander.h"

Wander::Wander(ActionUser* ActionUser)
{
	this->_ActionUser = ActionUser;

	this->targetX = this->targetY = -1;
	this->_Map = &WorldMap;
}

bool Wander::isActionInRange()
{
	return false;
}

bool Wander::isActionFinished()
{
	if (this->_ActionUser->getPositionX() == this->targetX && this->_ActionUser->getPositionY() == this->targetY) {
		return true;
	}

	return false;
}

void Wander::doAction()
{
}

void Wander::findTarget()
{
	MapCoordinates GoalCoordinates(rand() % this->_Map->numberOfTilesX, rand() % this->_Map->numberOfTilesY);
	while (!WorldMap.coordinatesAreWithinMap(GoalCoordinates)) {
		GoalCoordinates = MapCoordinates::MapCoordinates(rand() % this->_Map->numberOfTilesX, rand() % this->_Map->numberOfTilesY);
	}

	this->targetX = GoalCoordinates.x * MAP_TILE_SIZE + MAP_TILE_SIZE/2;
	this->targetY = GoalCoordinates.y * MAP_TILE_SIZE + MAP_TILE_SIZE/2;
}