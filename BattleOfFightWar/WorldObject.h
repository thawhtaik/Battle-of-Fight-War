#ifndef _WORLD_OBJECT
#define _WORLD_OBJECT

#include "Target.h"
#include "Attacker.h"

class WorldObject: public Target, public Attacker
{

	public:

		int objectIndex;
		
		int positionX, positionY;

		int sizeX, sizeY;

		virtual void releaseWorldObject() = 0;

		virtual void update() = 0;
		virtual void render() = 0;

		virtual int getIndex() = 0;
		virtual int getPositionX() = 0;
		virtual int getPositionY() = 0;
		virtual int getFacing() = 0;
};

#endif