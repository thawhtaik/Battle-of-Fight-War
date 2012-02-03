#ifndef _ACTION_USER
#define _ACTION_USER

#include "Weapon.h"
#include "LifeStatus.h"

class ActionUser: public WorldObject
{
	public:

		virtual void attack() = 0;
		virtual int getIndex() = 0;

		virtual LifeStatus* getLifeStatus() = 0;
		virtual Weapon* getCurrentWeapon() = 0;

		virtual int getPositionX() = 0;
		virtual int getPositionY() = 0;
		virtual int getFacing() = 0;

		virtual void setCurrentAnimation(int newAnimation) = 0;
		virtual void setAnimationEffect(int newAnimation) = 0;
};

#endif