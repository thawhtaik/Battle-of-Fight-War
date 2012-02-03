#ifndef _WEAPON_GRAPHICS
#define _WEAPON_GRAPHICS

#include "Sprite.h"
#include "TexturePack.h"
#include "AllConstants.h"
#include "MapCoordinates.h"

#include "WeaponSelector.h"

#define WEAPON_ANIMATION_IDLE 0
#define WEAPON_ANIMATION_ATTACKING 1

#define WEAPON_SPRITESHEET_NUMBER_OF_COLUMNS 1
#define WEAPON_MUZZLE_FLASH_SPRITESHEET_NUMBER_OF_COLUMNS 3

#define WEAPON_SPRITE_ROW_SOUTH 0
#define WEAPON_SPRITE_ROW_NORTH 1
#define WEAPON_SPRITE_ROW_SIDE 2

#define WEAPON_SPRITE_SIZE 64
#define WEAPON_MUZZLE_FLASH_SPRITE_SIZE 24

extern TexturePack GlobalTexturePack;
extern DirectXStuff GlobalDirectXStuff;

class WeaponGraphics
{
	public:
		WeaponGraphics();
		void releaseWeaponGraphics();

		void render();
		void animate();
		void animateWithShakeInYDirection();

		void setCurrentSpriteFacing(int newFacing);
		void setCurrentAnimationState(int newAnimationEffect);
		void setWeaponType(short newWeaponType);
		
		void setAnimationEffect(int newAnimationEffect);

		MapCoordinates MapPosition;

	private:

		void _determineMuzzleFlashPosition();
		void _callMuzzleFlashRender();
		void _renderMuzzleFlash();
		void _doNotRenderMuzzleFlash();

		short _currentFacing;
		short _currentSpriteRow;
		short _currentAnimationState;

		short _offsetX;
		short _offsetY;

		//FOR DOING ALL SPRITE-RELATED STUFF
		LPD3DXSPRITE _SpriteObj;
		LPDIRECT3DTEXTURE9* _WeaponTexture;
		LPDIRECT3DTEXTURE9* _MuzzleFlashTexture;

		Sprite _WeaponSprite;
		Sprite _MuzzleFlashSprite;

		//Function pointers awwww yeah
		void (WeaponGraphics::*_renderMuzzleFlashFunctionPointer)();
};


#endif