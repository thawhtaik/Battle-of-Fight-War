#ifndef _BRAIN_
#define _BRAIN_

#include "Pathfinder.h"
#include "DirectionFinder.h"

#include "LifeStatus.h"
#include "Goal.h"

#include "Wander.h"
#include "SearchForThreats.h"

extern Map WorldMap;

class Brain
{

	public:
		Brain();
		Brain(Map *Map);

		void releaseBrain();
		
		//Direction-finding stuff -----------------
		Goal* determineGoal(ActionUser* BrainGuy);
		
		std::vector<MapCoordinates> getPathFromGoal(MapCoordinates CurrentPosition, Goal* CurrentGoal);
		
		int getMovementDirectionFromCurrentPosition(MapCoordinates CurrentPosition, std::vector<MapCoordinates>* CurrentPath, int currentPathIndex);

	private:

		Map* _Map;
		
};

#endif