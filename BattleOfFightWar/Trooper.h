#ifndef _TROOPER_
#define _TROOPER_


#include "TrooperGraphics.h"

#include "LivingEntity.h"
#include "Brain.h"

const int TROOPER_MOVEMENT_IDLE = 0;
const int TROOPER_MOVEMENT_SOUTH = 1;
const int TROOPER_MOVEMENT_NORTH = 2;
const int TROOPER_MOVEMENT_EAST = 3;
const int TROOPER_MOVEMENT_WEST = 4;

const int TROOPER_MOVEMENT_SOUTHEAST = 5;
const int TROOPER_MOVEMENT_SOUTHWEST = 6;
const int TROOPER_MOVEMENT_NORTHEAST = 7;
const int TROOPER_MOVEMENT_NORTHWEST = 8;

extern Map WorldMap;

class Trooper: public LivingEntity
{
	public:

		Trooper();
		Trooper(TrooperGraphics *NewTrooperGraphics);

		bool isPositionInObjectHitbox(MapCoordinates Position);

		void releaseWorldObject();

		void initLivingEntityGraphics();

		void setCurrentPath(std::vector<MapCoordinates> NewPath);

};

#endif