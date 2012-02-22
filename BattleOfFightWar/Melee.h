#ifndef _WEAPON_MELEE_
#define _WEAPON_MELEE_

#include "Weapon.h"

#define WEAPON_MELEE_WIND_UP_TIME_NORMAL 80

class Melee: public Weapon
{

	public:

		Melee(int newAttackPower, int newRange, int newCoolDown, int newWindUpTime);
		void attack(WorldObject* Attacker, MapCoordinates TargetPosition);
};


#endif