#ifndef _ACTION_
#define _ACTION_

#include <cmath>

#include "MapCoordinates.h"
#include "ActionUser.h"
#include "AnimatedEffectCreator.h"
#include "AllConstants.h"


class Action
{

	public:

		Action();
		virtual bool isActionFinished() = 0;
		virtual void doAction() = 0;
		virtual void releaseAction() = 0;

	protected:

		short _actionStartTime;
		short _actionWindUpTime;
		short _timeTick;

		ActionUser* _ActionUser;

};


#endif