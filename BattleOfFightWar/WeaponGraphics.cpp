#include "WeaponGraphics.h"

WeaponGraphics::WeaponGraphics()
{
	this->_SpriteObj = NULL;
	this->_SpriteObj = GlobalDirectXStuff.spriteObj; //Since we should only use one sprite object

	this->_WeaponTexture = NULL;
	this->_MuzzleFlashTexture = &GlobalTexturePack.MuzzleFlashTexture;

	this->_currentFacing = -1; //Doing this for now so it responds to setFacing calls
	this->_currentSpriteRow = -1;

	this->_WeaponSprite = Sprite::Sprite(
		0, 
		WEAPON_SPRITESHEET_NUMBER_OF_COLUMNS, 
		WEAPON_SPRITE_SIZE, WEAPON_SPRITE_SIZE,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	this->_MuzzleFlashSprite = Sprite::Sprite(
		0,
		WEAPON_MUZZLE_FLASH_SPRITESHEET_NUMBER_OF_COLUMNS,
		WEAPON_MUZZLE_FLASH_SPRITE_SIZE, WEAPON_MUZZLE_FLASH_SPRITE_SIZE,
		D3DCOLOR_XRGB(255, 255, 255),
		1.0, 1.0, 0.0,
		0, 4
	);

	this->_offsetX = 0;
	this->_offsetY = 0;

	this->_WeaponSprite.delay = ANIMATION_DELAY_NORMAL;
	this->_MuzzleFlashSprite.delay = ANIMATION_DELAY_QUICK;

	this->_renderMuzzleFlashFunctionPointer = &WeaponGraphics::_doNotRenderMuzzleFlash;
}

void WeaponGraphics::releaseWeaponGraphics()
{
	this->_SpriteObj = NULL; //Don't release this unless the weapon has its own sprite object!

	this->_WeaponTexture = NULL;
	this->_MuzzleFlashTexture = NULL;

	this->_renderMuzzleFlashFunctionPointer = NULL;
}

void WeaponGraphics::animate()
{
	this->_WeaponSprite.x = (float)this->MapPosition.x + this->_offsetX;
	this->_WeaponSprite.y = (float)this->MapPosition.y + this->_offsetY;

	/*switch (this->_currentAnimationState) {
		case WEAPON_ANIMATION_IDLE:
			return;
		case WEAPON_ANIMATION_ATTACKING:
			return;
		default:
			break;
	}*/

	//this->_WeaponSprite.animate(); //Necessary unless the weapon is actually animated? i.e. bouncing/firing/blowing up
}


void WeaponGraphics::animateWithShakeInYDirection()
{
	this->animate();
	this->_WeaponSprite.animateWithShakeInYDirection();
}


void WeaponGraphics::render()
{
	if (this->_WeaponTexture != NULL) {

		this->_WeaponSprite.spriteTransformDraw(*this->_WeaponTexture, this->_SpriteObj);
		(this->*_renderMuzzleFlashFunctionPointer)();
	}
	
}


void WeaponGraphics::setCurrentSpriteFacing(int newFacing)
{
	if (this->_currentFacing == newFacing) {
		return;
	}

	this->_currentFacing = newFacing;

	//Ugggh trial and error
	switch (this->_currentFacing) {
		case ENTITY_FACING_SOUTH:
			this->_currentSpriteRow = WEAPON_SPRITE_ROW_SOUTH;
			this->_WeaponSprite.frame = this->_WeaponSprite.endFrame = this->_WeaponSprite.startFrame = this->_currentSpriteRow;
			this->_WeaponSprite.scalingX = +1;
			this->_offsetX = -13;
			this->_offsetY = -3;
			break;
		case ENTITY_FACING_SOUTHEAST:
			this->_currentSpriteRow = WEAPON_SPRITE_ROW_SOUTHEAST;
			this->_WeaponSprite.frame = this->_WeaponSprite.endFrame = this->_WeaponSprite.startFrame = this->_currentSpriteRow;
			this->_WeaponSprite.scalingX = +1;
			this->_offsetX = +7;
			this->_offsetY = -7;
			break;
		case ENTITY_FACING_SOUTHWEST:
			this->_currentSpriteRow = WEAPON_SPRITE_ROW_SOUTHEAST;
			this->_WeaponSprite.frame = this->_WeaponSprite.endFrame = this->_WeaponSprite.startFrame = this->_currentSpriteRow;
			this->_WeaponSprite.scalingX = -1;
			this->_offsetX = +TROOPER_BODY_SPRITE_SIZE_HALF + 14;
			this->_offsetY = -7;
			break;
		case ENTITY_FACING_NORTH:
			this->_currentSpriteRow = WEAPON_SPRITE_ROW_NORTH;
			this->_WeaponSprite.frame = this->_WeaponSprite.endFrame = this->_WeaponSprite.startFrame = this->_currentSpriteRow;
			this->_WeaponSprite.scalingX = +1;
			this->_offsetX = +13;
			this->_offsetY = -(TROOPER_BODY_SPRITE_SIZE_HALF);
			break;
		case ENTITY_FACING_NORTHEAST:
			this->_currentSpriteRow = WEAPON_SPRITE_ROW_NORTHEAST;
			this->_WeaponSprite.frame = this->_WeaponSprite.endFrame = this->_WeaponSprite.startFrame = this->_currentSpriteRow;
			this->_WeaponSprite.scalingX = +1;
			this->_offsetX = +TROOPER_BODY_SPRITE_SIZE_HALF - 6;
			this->_offsetY = -15;
			break;
		case ENTITY_FACING_NORTHWEST:
			this->_currentSpriteRow = WEAPON_SPRITE_ROW_NORTHEAST;
			this->_WeaponSprite.frame = this->_WeaponSprite.endFrame = this->_WeaponSprite.startFrame = this->_currentSpriteRow;
			this->_WeaponSprite.scalingX = -1;
			this->_offsetX = +TROOPER_BODY_SPRITE_SIZE_HALF + 6;
			this->_offsetY = -15;
			break;
		case ENTITY_FACING_EAST:
			this->_currentSpriteRow = WEAPON_SPRITE_ROW_SIDE;
			this->_WeaponSprite.frame = this->_WeaponSprite.endFrame = this->_WeaponSprite.startFrame = this->_currentSpriteRow;
			this->_WeaponSprite.scalingX = +1;
			this->_offsetX = +5;
			this->_offsetY = -12;
			break;
		case ENTITY_FACING_WEST:
			this->_currentSpriteRow = WEAPON_SPRITE_ROW_SIDE;
			this->_WeaponSprite.frame = this->_WeaponSprite.endFrame = this->_WeaponSprite.startFrame = this->_currentSpriteRow;
			this->_WeaponSprite.scalingX = -1;
			this->_offsetX = +40;
			this->_offsetY = -12;
			break;
		default:
			break;
	}
}


void WeaponGraphics::setCurrentAnimationState(int newAnimationState)
{
	this->_currentAnimationState = newAnimationState;
}


void WeaponGraphics::setAnimationEffect(int newAnimationEffect)
{
	switch (newAnimationEffect) {

		case ANIMATION_EFFECT_MUZZLE_FLASH:
			this->_renderMuzzleFlashFunctionPointer = &WeaponGraphics::_renderMuzzleFlash;
			this->_MuzzleFlashSprite.frame = 0;
			break;
		case ANIMATION_EFFECT_STOP_MUZZLE_FLASH:
			this->_renderMuzzleFlashFunctionPointer = &WeaponGraphics::_doNotRenderMuzzleFlash;
			break;
		default:
			break;
	}
}


void WeaponGraphics::setWeaponType(short newWeaponType)
{
	this->_WeaponTexture = WeaponSelector::getWeaponTextureBasedOnType(newWeaponType);
}


void WeaponGraphics::_renderMuzzleFlash()
{
	this->_determineMuzzleFlashPosition();
	this->_MuzzleFlashSprite.spriteTransformDraw(*this->_MuzzleFlashTexture, this->_SpriteObj);
	this->_MuzzleFlashSprite.animate();

	if (this->_MuzzleFlashSprite.frame == 0) {
		this->setAnimationEffect(ANIMATION_EFFECT_STOP_MUZZLE_FLASH);
		return;
	}
}


void WeaponGraphics::_doNotRenderMuzzleFlash()
{
}


void WeaponGraphics::_determineMuzzleFlashPosition()
{
	/**
		Again, terribly hard-coded. Figure out a way to calculate this using hard-coded weapon type x/y lengths
	*/
	switch (this->_currentFacing) {
		case ENTITY_FACING_SOUTH:
			this->_MuzzleFlashSprite.x = (float)this->MapPosition.x + 6;
			this->_MuzzleFlashSprite.y = (float)this->MapPosition.y + 36;
			break;
		case ENTITY_FACING_NORTH:
			this->_MuzzleFlashSprite.x = (float)this->MapPosition.x + 31;
			this->_MuzzleFlashSprite.y = (float)this->MapPosition.y - TROOPER_BODY_SPRITE_SIZE_HALF;
			break;
		case ENTITY_FACING_EAST:
			this->_MuzzleFlashSprite.x = (float)this->MapPosition.x + TROOPER_BODY_SPRITE_SIZE;
			this->_MuzzleFlashSprite.y = (float)this->MapPosition.y + 5;
			break;
		case ENTITY_FACING_WEST:
			this->_MuzzleFlashSprite.x = (float)this->MapPosition.x - TROOPER_BODY_SPRITE_SIZE_HALF;
			this->_MuzzleFlashSprite.y = (float)this->MapPosition.y + 5;
			break;
		case ENTITY_FACING_SOUTHEAST:
			this->_MuzzleFlashSprite.x = (float)this->MapPosition.x + TROOPER_BODY_SPRITE_SIZE;
			this->_MuzzleFlashSprite.y = (float)this->MapPosition.y + 36;
			break;
		case ENTITY_FACING_SOUTHWEST:
			this->_MuzzleFlashSprite.x = (float)this->MapPosition.x - TROOPER_BODY_SPRITE_SIZE_HALF;
			this->_MuzzleFlashSprite.y = (float)this->MapPosition.y + 36;
			break;
		case ENTITY_FACING_NORTHEAST:
			this->_MuzzleFlashSprite.x = (float)this->MapPosition.x + TROOPER_BODY_SPRITE_SIZE + 7;
			this->_MuzzleFlashSprite.y = (float)this->MapPosition.y - TROOPER_BODY_SPRITE_SIZE_HALF + 7;
			break;
		case ENTITY_FACING_NORTHWEST:
			this->_MuzzleFlashSprite.x = (float)this->MapPosition.x - TROOPER_BODY_SPRITE_SIZE_HALF - 7;
			this->_MuzzleFlashSprite.y = (float)this->MapPosition.y - TROOPER_BODY_SPRITE_SIZE_HALF + 7;
			break;
	}
}
