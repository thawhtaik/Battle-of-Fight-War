#ifndef _WEAPON_RANGED_
#define _WEAPON_RANGED_

#include "Weapon.h"

#include "Bullet.h"
#include "ProjectileList.h"

#define WEAPON_RANGED_WIND_UP_TIME_NORMAL 1

#define WEAPON_RANGED_MUZZLE_FLASH_OFFSET 0

extern ProjectileList GlobalProjectileList;

class RangedWeapon: public Weapon
{

	public:
		RangedWeapon(int newAttackPower, int newRange, int newCoolDown);
		void attack(WorldObject* Attacker, MapCoordinates TargetPosition);
};


#endif