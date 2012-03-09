#include "Bullet.h"

Bullet::Bullet(MapCoordinates NewPosition, MapCoordinates TargetPosition, int newAttackPower, int newVelocity, short newFacing)
{
	this->Position = NewPosition;
	this->_TargetPosition = TargetPosition;
	this->_attackPower = newAttackPower;
	this->_facing = newFacing;

	this->_ProjectileSprite = Sprite::Sprite(
		0, 
		BULLET_SPRITESHEET_NUMBER_OF_COLUMNS,
		BULLET_SPRITE_WIDTH,
		BULLET_SPRITE_HEIGHT,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	this->_ProjectileTexture = &GlobalTexturePack.BulletTexture;

	this->_determineMovement(newVelocity);
}


void Bullet::render()
{
	this->_ProjectileSprite.spriteTransformDraw(*this->_ProjectileTexture, GlobalDirectXStuff.spriteObj);
}
