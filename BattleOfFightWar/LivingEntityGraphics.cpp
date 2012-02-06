#include "LivingEntityGraphics.h"

LivingEntityGraphics::LivingEntityGraphics()
{
	this->positionX = this->positionY = 0;

	this->_SpriteObj = NULL;
	this->_SpriteObj = GlobalDirectXStuff.spriteObj; //Since we should only use one sprite object

	this->_WeaponGraphics = NULL; //In case they don't set it "down there"
}


void LivingEntityGraphics::setAnimationEffect(int newAnimationEffect)
{
	switch (newAnimationEffect) {
		case ANIMATION_EFFECT_BLEEDING:
			break;
		case ANIMATION_EFFECT_STOP_BLEEDING:
			break;
		case ANIMATION_EFFECT_MUZZLE_FLASH:
			this->_WeaponGraphics->setAnimationEffect(ANIMATION_EFFECT_MUZZLE_FLASH);
			break;
		case ANIMATION_EFFECT_STOP_MUZZLE_FLASH:
			this->_WeaponGraphics->setAnimationEffect(ANIMATION_EFFECT_STOP_MUZZLE_FLASH);
			break;
		default:
			return;
			break;
	}
}


void LivingEntityGraphics::setWeaponType(short newWeaponType)
{
	this->_WeaponGraphics->setWeaponType(newWeaponType);
}