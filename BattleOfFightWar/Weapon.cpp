#include "Weapon.h"

Weapon::Weapon()
{
	this->_weaponType = WEAPON_TYPE_UNARMED;

	this->_damageType = 0;
}


bool Weapon::_isTargetInDamageRange(WorldObject* Attacker, WorldObject* AttackTarget)
{
	int attackerPositionX = Attacker->getPositionX();
	int attackerPositionY = Attacker->getPositionY();

	int targetPositionX = AttackTarget->getPositionX();
	int targetPositionY = AttackTarget->getPositionY();

	double distanceSquared = pow((double)(targetPositionX - attackerPositionX), 2) + pow((double)(targetPositionY - attackerPositionY), 2);
	if (distanceSquared <= pow((double)WEAPON_damageTarget_RANGE_MELEE, 2)) {
		return true;
	}

	return false;
}

int Weapon::getAttackWindUpTime()
{
	return this->_attackWindUpTime;
}


