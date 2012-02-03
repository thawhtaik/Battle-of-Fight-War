#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(int newAttackPower, int newRange, int newCoolDown)
{
	this->_attackPower = newAttackPower;
	this->_range = newRange;
	this->_coolDown = newCoolDown;
	this->_attackWindUpTime = WEAPON_RANGED_WIND_UP_TIME_NORMAL;
}

void RangedWeapon::attack(WorldObject* Attacker)
{
	int attackerPositionX = Attacker->getPositionX();
	int attackerPositionY = Attacker->getPositionY();

	short facing = Attacker->getFacing();

	//Ugh, I trial-and-error'd these numbers
	MapCoordinates BulletPosition = MapCoordinates();
	switch (facing) {
		case ENTITY_FACING_SOUTH:
			BulletPosition.y = attackerPositionY + 27;
			BulletPosition.x = attackerPositionX - 5;
			break;
		case ENTITY_FACING_NORTH:
			BulletPosition.y = attackerPositionY - 26;
			BulletPosition.x = attackerPositionX + 31;
			break;
		case ENTITY_FACING_EAST:
			BulletPosition.y = attackerPositionY + 5;
			BulletPosition.x = attackerPositionX + TROOPER_BODY_SPRITE_SIZE;
			break;
		case ENTITY_FACING_WEST:
			BulletPosition.y = attackerPositionY - 5;
			BulletPosition.x = attackerPositionX - TROOPER_BODY_SPRITE_SIZE_HALF;
			break;
		default:
			BulletPosition.y = attackerPositionY;
			BulletPosition.x = attackerPositionX;
			break;
	}

	//Based on weapon type, determine type of bullet to fired hyah
	Bullet* NewBullet = new Bullet(BulletPosition, facing, this->_attackPower, 15);
	GlobalProjectileList.add(NewBullet);

	//Add fired projectile to list of projectiles
}