#ifndef _PROJECTILE_LIST
#define _PROJECTILE_LIST

#include "Projectile.h"
#include <vector>

extern Map WorldMap;


class ProjectileList
{

	public:
		ProjectileList();
		void releaseProjectileList();

		void update();
		void render();

		void add(Projectile* NewProjectile);
		void removeAtIndex(int projectileIndex);

		Projectile* getAtIndex(int projectileIndex);
		int getSize();

	private:

		std::vector<Projectile*> _Projectiles;

};


#endif