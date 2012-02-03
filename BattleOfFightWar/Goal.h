#ifndef _GOAL_
#define _GOAL_

#include "ActionUser.h"
#include "Map.h"

extern Map WorldMap;

class Goal
{
	public:
		virtual bool isActionInRange() = 0;
		virtual bool isActionFinished() = 0;
		virtual void doAction() = 0;
		
		virtual void findTarget() = 0;
		void releaseGoal();

		int targetX, targetY;

	protected:
		Map* _Map;
		ActionUser* _ActionUser;

};

#endif