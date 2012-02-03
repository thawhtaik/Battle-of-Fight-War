#ifndef _SEARCH_ACTION
#define _SEARCH_ACTION

#include "ActionUser.h"
#include "Map.h"

extern Map WorldMap;

class SearchAction
{
	public:

		int targetPositionX, targetPositionY;

		virtual void search() = 0;
		void releaseSearchAction();

	protected:
		Map* _Map;
		ActionUser *_ActionUser;

};

#endif