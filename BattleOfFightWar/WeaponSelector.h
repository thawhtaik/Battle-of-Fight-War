#ifndef _WEAPON_SELECTOR_
#define _WEAPON_SELECTOR_

#include "Melee.h"
#include "RangedWeapon.h"
#include "TexturePack.h"

extern TexturePack GlobalTexturePack;

class WeaponSelector
{

	public: 
		WeaponSelector();

		static Weapon* getWeaponBasedOnType(short weaponType);
		static LPDIRECT3DTEXTURE9* getWeaponTextureBasedOnType(short weaponType);

};


#endif