#ifndef _GOAL_WANDER_
#define _GOAL_WANDER_

#include "Goal.h"

#include <time.h>

class Wander: public Goal
{

	public:
		Wander(ActionUser* ActionUser);

		void releaseGoal();

		bool isActionInRange();
		bool isActionFinished();
		void doAction();
		
		void findTarget();
};

#endif