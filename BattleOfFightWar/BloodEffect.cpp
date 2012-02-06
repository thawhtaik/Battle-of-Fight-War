#include "BloodEffect.h"

BloodEffect::BloodEffect(MapCoordinates NewPosition)
{
	this->_Position = NewPosition;

	int bloodSpriteSheetNumberOfColumns = 3;
	this->_BloodSprite = Sprite::Sprite(0, 3, SPRITE_SIZE_MEDIUM, SPRITE_SIZE_MEDIUM, D3DCOLOR_XRGB(255, 255, 255));
	this->_BloodSprite.endFrame = bloodSpriteSheetNumberOfColumns;
	this->_BloodSprite.delay = ENTITY_ANIMATION_DELAY;
	this->_BloodSprite.scalingX = this->_BloodSprite.scalingY = 1.5;


	this->_BloodSprite.x = (float)this->_Position.x;
	this->_BloodSprite.y = (float)this->_Position.y;
}


void BloodEffect::animate()
{
	this->_BloodSprite.animate();

	if (this->_BloodSprite.frame == 0) {
		this->_finished = true;
	}
}


void BloodEffect::render()
{
	this->_BloodSprite.spriteTransformDraw(GlobalTexturePack.BloodTexture, GlobalDirectXStuff.spriteObj);	
}