#include "Bullet.h"

Bullet::Bullet(MapCoordinates NewPosition, int newFacing, int newAttackPower, int newVelocity)
{
	this->Position = NewPosition;
	
	this->_facing = newFacing;
	this->_attackPower = newAttackPower;

	this->_ProjectileSprite = Sprite::Sprite(
		0, 
		BULLET_SPRITESHEET_NUMBER_OF_COLUMNS,
		BULLET_SPRITE_SIZE,
		BULLET_SPRITE_SIZE,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	this->_ProjectileTexture = &GlobalTexturePack.BulletTexture;

	this->_determineMovement(newVelocity);
}


void Bullet::render()
{
	this->_ProjectileSprite.spriteTransformDraw(*this->_ProjectileTexture, GlobalDirectXStuff.spriteObj);
}
