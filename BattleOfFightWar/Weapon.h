#ifndef _WEAPON_
#define _WEAPON_

#include "LivingEntitiesList.h"
#include "Map.h"
#include <math.h>

extern Map WorldMap;
extern LivingEntitiesList GlobalLivingEntitiesList;

#define WEAPON_DAMAGE_RANGE_MELEE 50

#define WEAPON_TYPE_UNARMED 0
#define WEAPON_TYPE_RIFLE 1

#include "MapCoordinates.h"

class Weapon
{

	public:

		Weapon();

		virtual void attack(WorldObject* Attacker, MapCoordinates TargetPosition) = 0;
		int getAttackWindUpTime();

	protected:
		
		int _attackPower;
		int _range;
		int _attackWindUpTime;

		int _coolDown;

		short _weaponType;

		bool _isTargetInDamageRange(WorldObject* Attacker, WorldObject* AttackTarget);
		void _damage(WorldObject* AttacdkTarget);
		
};

#endif