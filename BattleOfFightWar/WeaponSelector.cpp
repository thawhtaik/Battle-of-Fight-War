#include "WeaponSelector.h"

WeaponSelector::WeaponSelector()
{
}


Weapon* WeaponSelector::getWeaponBasedOnType(short weaponType)
{
	switch (weaponType) {

		case WEAPON_TYPE_UNARMED:
			return new Melee(2, 10, 2, WEAPON_MELEE_WIND_UP_TIME_NORMAL);
			break;
		case WEAPON_TYPE_RIFLE:
			return new RangedWeapon(7, 50, 2);
			break;

	}
}


LPDIRECT3DTEXTURE9* WeaponSelector::getWeaponTextureBasedOnType(short weaponType)
{
	switch (weaponType) {

		case WEAPON_TYPE_UNARMED:
			return NULL;
			break;
		case WEAPON_TYPE_RIFLE:
			return &GlobalTexturePack.RifleTexture;
			break;

	}
}