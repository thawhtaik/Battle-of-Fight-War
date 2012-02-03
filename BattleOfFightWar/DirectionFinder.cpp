#include "DirectionFinder.h"

DirectionFinder::DirectionFinder()
{
}


int DirectionFinder::getMovementDirectionToCoordinates(MapCoordinates CurrentCoordinates, MapCoordinates GoalCoordinates)
{
	int movement = MOVEMENT_DIRECTION_IDLE;
	if (GoalCoordinates.y > CurrentCoordinates.y) {
		
		movement = MOVEMENT_DIRECTION_SOUTH;
		if (GoalCoordinates.x > CurrentCoordinates.x) {
			movement = MOVEMENT_DIRECTION_SOUTHEAST;
		} else if (GoalCoordinates.x < CurrentCoordinates.x) {
			movement = MOVEMENT_DIRECTION_SOUTHWEST;
		}

	} else if (GoalCoordinates.y < CurrentCoordinates.y) {

		movement = MOVEMENT_DIRECTION_NORTH;
		if (GoalCoordinates.x > CurrentCoordinates.x) {
			movement = MOVEMENT_DIRECTION_NORTHEAST;
		} else if (GoalCoordinates.x < CurrentCoordinates.x) {
			movement = MOVEMENT_DIRECTION_NORTHWEST;
		}

	} else if (GoalCoordinates.x > CurrentCoordinates.x) {

		movement = MOVEMENT_DIRECTION_EAST;

	} else if (GoalCoordinates.x < CurrentCoordinates.x) {

		movement = MOVEMENT_DIRECTION_WEST;

	}

	return movement;
}