#ifndef _PROJECTILE_
#define _PROJECTILE_

#define _USE_MATH_DEFINES

#include <math.h>

#include "MapCoordinates.h"
#include "AllConstants.h"

#include "Sprite.h"
#include "TexturePack.h"

#include "LivingEntitiesList.h"
#include "Map.h"


extern TexturePack GlobalTexturePack;
extern DirectXStuff GlobalDirectXStuff;

extern Map WorldMap;
extern LivingEntitiesList GlobalLivingEntitiesList;

class Projectile
{

	public:
		Projectile();
		void releaseProjectile();

		void update();
		virtual void render() = 0;

		bool isFunctional();

		MapCoordinates Position;

	protected:

		void _determineMovement(short newVelocity);
		
		bool _hasCollisionOnTile(MapTile* MapTile);

		LPDIRECT3DTEXTURE9* _ProjectileTexture;
		Sprite _ProjectileSprite;

		bool _functional;

		long _distanceTravelled;
		short _attackPower;
		
		short _xVelocity;
		short _yVelocity;

		short _facing;
		
		short _amountOfCoverPassed;

};


#endif