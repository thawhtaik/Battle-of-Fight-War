#ifndef _BULLET_
#define _BULLET_

#include "Projectile.h"

class Bullet : public Projectile
{

	public:
		Bullet(MapCoordinates NewPosition, MapCoordinates TargetPosition, int newAttackPower, int newVelocity, short newFacing);

		void render();
};


#endif