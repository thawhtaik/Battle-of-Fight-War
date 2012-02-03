#include "Action.h"
#include "AllConstants.h"

#ifndef _ACTION_TAKE_DAMAGE_
#define _ACTION_TAKE_DAMAGE_

extern TexturePack GlobalTexturePack;
extern DirectXStuff GlobalDirectXStuff;

class TakeDamageAction : public Action
{

	public:
		TakeDamageAction(ActionUser* ActionUser);
		void releaseAction();

		void doAction();
		bool isActionFinished();

	private:

		bool _damageFinished;
};

#endif