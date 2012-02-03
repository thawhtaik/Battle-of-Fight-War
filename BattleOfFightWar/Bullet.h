#ifndef _BULLET_
#define _BULLET_

#include "Projectile.h"

class Bullet : public Projectile
{

	public:
		Bullet(MapCoordinates NewPosition, int newFacing, int newAttackPower, int newVelocity);

		void render();
};


#endif