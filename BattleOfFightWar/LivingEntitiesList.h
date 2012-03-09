#ifndef _LIVING_ENTITIES_LIST_
#define _LIVING_ENTITIES_LIST_

#include "WorldObject.h"
#include "Map.h"

#include <vector>

extern Map WorldMap;


class LivingEntitiesList
{

	public:
		LivingEntitiesList();
		void releaseLivingEntitiesList();

		void add(WorldObject* NewLivingEntity);
		void removeAtIndex(int livingEntityIndex);

		WorldObject* getAtIndex(int livingEntityIndex);
		int getSize();

	private:

		std::vector<WorldObject*> _LivingEntities;

};

#endif