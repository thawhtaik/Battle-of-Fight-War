#include "LivingEntityGraphics.h"

LivingEntityGraphics::LivingEntityGraphics()
{
	this->positionX = this->positionY = 0;

	this->_BloodTexture = &GlobalTexturePack.BloodTexture;

	int bloodSpriteSheetNumberOfColumns = 3;
	this->_Blood = Sprite::Sprite(0, 3, SPRITE_SIZE_MEDIUM, SPRITE_SIZE_MEDIUM, D3DCOLOR_XRGB(255, 255, 255));
	this->_Blood.endFrame = bloodSpriteSheetNumberOfColumns;
	this->_Blood.delay = ENTITY_ANIMATION_DELAY;
	this->_Blood.scalingX = this->_Blood.scalingY = 1.5;

	this->_renderBlood = false;

	this->_SpriteObj = NULL;
	this->_SpriteObj = GlobalDirectXStuff.spriteObj; //Since we should only use one sprite object

	this->_WeaponGraphics = NULL; //In case they don't set it "down there"
}


void LivingEntityGraphics::renderBloodOn()
{
	this->_renderBlood = true;
}


void LivingEntityGraphics::renderBloodOff()
{
	this->_renderBlood = false;
}

void LivingEntityGraphics::setAnimationEffect(int newAnimationEffect)
{
	switch (newAnimationEffect) {
		case ANIMATION_EFFECT_BLEEDING:
			this->_renderBlood = true;
			break;
		case ANIMATION_EFFECT_STOP_BLEEDING:
			this->_renderBlood = false;
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