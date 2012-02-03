#ifndef _MOVEMENT_COLLISION_CHECKER_
#define _MOVEMENT_COLLISION_CHECKER_

#include "Map.h"
#include "LivingEntitiesList.h"

extern Map WorldMap;
extern LivingEntitiesList GlobalLivingEntitiesList;

class MovementCollisionChecker
{

	public:

		MovementCollisionChecker();
		static bool isLivingEntityInPosition(MapCoordinates Position, int sizeX, int sizeY, int objectIndex);
};


#endif