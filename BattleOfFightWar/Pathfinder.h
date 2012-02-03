#ifndef _PATHFINDER_
#define _PATHFINDER_

#include "Map.h"

static const float G_WEIGHT = 1.0;
static const float H_WEIGHT = 1.0;
static const float COST_WEIGHT = 1.0;

class Pathfinder
{
	public:
		Pathfinder();
		static std::vector<MapCoordinates> getPath(Map *Map, MapCoordinates Start, MapCoordinates Goal);

	private:

		static float _getDistanceBetweenPoints(MapCoordinates A, MapCoordinates B);
};

#endif