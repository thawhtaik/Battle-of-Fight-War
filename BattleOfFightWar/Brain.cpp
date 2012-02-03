#include "Brain.h"

Brain::Brain()
{
	this->_Map = &WorldMap;
}

Brain::Brain(Map *Map)
{
	this->_Map = Map;
}

void Brain::releaseBrain()
{
	this->_Map = NULL;
}

std::vector<MapCoordinates> Brain::getPathFromGoal(MapCoordinates CurrentPosition, Goal* CurrentGoal)
{
	MapTile *StartTile = this->_Map->getTileAtPosition(CurrentPosition.x, CurrentPosition.y);
	MapTile *GoalTile = this->_Map->getTileAtPosition(CurrentGoal->targetX, CurrentGoal->targetY);

	return Pathfinder::getPath(this->_Map, StartTile->TileCoordinates, GoalTile->TileCoordinates);
}

Goal* Brain::determineGoal(ActionUser* BrainGuy)
{
	Wander* NewAction = new Wander(BrainGuy);

	return NewAction;
}

int Brain::getMovementDirectionFromCurrentPosition(MapCoordinates CurrentPosition, std::vector<MapCoordinates>* CurrentPath, int currentPathIndex)
{
	MapTile *CurrentTile = this->_Map->getTileAtPosition(CurrentPosition.x, CurrentPosition.y);
	MapCoordinates CurrentCoordinates = CurrentTile->TileCoordinates;

	MapCoordinates CurrentGoalCoordinates = CurrentPath->at(currentPathIndex);

	//Check if we're on the final path coordinates
	if (currentPathIndex == CurrentPath->size() - 1) {

		//Get center of final path coordinates
		int currentGoalPositionX = CurrentGoalCoordinates.x * MAP_TILE_SIZE + MAP_TILE_SIZE/2;
		int currentGoalPositionY = CurrentGoalCoordinates.y * MAP_TILE_SIZE + MAP_TILE_SIZE/2;

		//Are we at the center of the final path coordinates?
		if (CurrentPosition.x == currentGoalPositionX && CurrentPosition.y == currentGoalPositionY) {
			return MOVEMENT_DIRECTION_IDLE;
		}

		//Not done? Then start moving toward center of final path coordinates
		MapCoordinates GoalPosition = MapCoordinates::MapCoordinates(currentGoalPositionX, currentGoalPositionY);

		return  DirectionFinder::getMovementDirectionToCoordinates(CurrentPosition, GoalPosition);
	}

	return DirectionFinder::getMovementDirectionToCoordinates(CurrentCoordinates, CurrentGoalCoordinates);
}