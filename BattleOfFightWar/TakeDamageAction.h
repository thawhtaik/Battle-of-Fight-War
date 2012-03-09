#include "Action.h"
#include "AllConstants.h"

#ifndef _ACTION_TAKE_DAMAGE_
#define _ACTION_TAKE_DAMAGE_

#include "Sprite.h"


class TakeDamageAction : public Action
{

	public:
		TakeDamageAction(ActionUser* ActionUser, int damage, short damageType, short damageDirection);
		void releaseAction();

		void doAction();
		bool isActionFinished();

	private:

		int _damage;
		short _damageType;

		bool _damageTargetFinished;
};

#endif