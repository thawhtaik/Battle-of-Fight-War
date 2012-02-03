#ifndef _DIRECTION_FINDER_
#define _DIRECTION_FINDER_

#include "Map.h"

const int MOVEMENT_DIRECTION_IDLE = 0;
const int MOVEMENT_DIRECTION_SOUTH = 1;
const int MOVEMENT_DIRECTION_NORTH = 2;
const int MOVEMENT_DIRECTION_EAST = 3;
const int MOVEMENT_DIRECTION_WEST = 4;

const int MOVEMENT_DIRECTION_SOUTHEAST = 5;
const int MOVEMENT_DIRECTION_SOUTHWEST = 6;
const int MOVEMENT_DIRECTION_NORTHEAST = 7;
const int MOVEMENT_DIRECTION_NORTHWEST = 8;

class DirectionFinder
{

	public:
		DirectionFinder();

		static int getMovementDirectionToCoordinates(MapCoordinates CurrentCoordinates, MapCoordinates GoalCoordinates);
};

#endif