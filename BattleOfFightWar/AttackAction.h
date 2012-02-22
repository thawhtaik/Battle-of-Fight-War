#include "Action.h"
#include "AllConstants.h"

#ifndef _ACTION_ATTACK_
#define _ACTION_ATTACK_

class AttackAction : public Action
{

	public:
		AttackAction(ActionUser* ActionUser, MapCoordinates TargetPosition);
		void releaseAction();

		void doAction();
		bool isActionFinished();

	private:

		MapCoordinates _TargetPosition;
		bool _attackFinished;
};

#endif
