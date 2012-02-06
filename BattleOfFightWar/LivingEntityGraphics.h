#ifndef _LIVING_ENTITY_GRAPHICS
#define _LIVING_ENTITY_GRAPHICS

#include "Sprite.h"
#include "TexturePack.h"
#include "AllConstants.h"

#include "WeaponGraphics.h"

extern TexturePack GlobalTexturePack;
extern DirectXStuff GlobalDirectXStuff;

class LivingEntityGraphics
{
	public:

		LivingEntityGraphics();
		virtual void releaseLivingEntityGraphics() = 0;

		virtual void render() = 0;
		virtual void animate() = 0;

		virtual void setCurrentSpriteFacing(int newFacing) = 0;
		virtual void setCurrentAnimationState(int newAnimationEffect) = 0;
		void setWeaponType(short newWeaponType);
		
		void setAnimationEffect(int newAnimationEffect);

		int positionX;
		int positionY;

	protected:

		WeaponGraphics* _WeaponGraphics;

		//FOR DOING ALL SPRITE-RELATED STUFF
		LPD3DXSPRITE _SpriteObj;
};

#endif