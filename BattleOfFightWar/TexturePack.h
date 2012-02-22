#ifndef _TEXTURE_PACK_
#define _TEXTURE_PACK_

#include "DirectXStuff.h"

extern DirectXStuff GlobalDirectXStuff;

class TexturePack
{
	public:

		TexturePack();

		bool initTexturePack();
		void releaseTexturePack();

		//Living Entities
		LPDIRECT3DTEXTURE9 HeadTexture;
		LPDIRECT3DTEXTURE9 BodyTexture;
		LPDIRECT3DTEXTURE9 BloodTexture;

		//Weapons
		LPDIRECT3DTEXTURE9 RifleTexture;
		LPDIRECT3DTEXTURE9 MuzzleFlashTexture;
		
		//Projectiles
		LPDIRECT3DTEXTURE9 BulletTexture;

		//Terrain 
		LPDIRECT3DSURFACE9 MapTilesSurface;

		//UI
		LPDIRECT3DTEXTURE9 TargetCursorTexture;
};

#endif