#include "TrooperGraphics.h"

TrooperGraphics::TrooperGraphics()
{
	this->_HeadTexture = &GlobalTexturePack.HeadTexture;
	this->_BodyTexture = &GlobalTexturePack.BodyTexture;

	this->_currentSpriteRow = TROOPER_SPRITE_ROW_SOUTH;

	this->Head = Sprite::Sprite(
		0, 
		TROOPER_HEAD_SPRITESHEET_NUM_COLUMNS, 
		TROOPER_SPRITE_SIZE_SMALL, TROOPER_SPRITE_SIZE_SMALL
	);

	this->Body = Sprite::Sprite(
		0, 
		TROOPER_BODY_SPRITESHEET_NUM_COLUMNS, 
		TROOPER_BODY_SPRITE_SIZE, TROOPER_BODY_SPRITE_SIZE,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	this->_initTrooperGraphics();
}

void TrooperGraphics::_initTrooperGraphics()
{
	this->positionX = 0;
	this->positionY = 0;

	//Weapon Init! Must do this early due to the other methods in this class that assume WeaponGraphics has been initialized!
	this->_WeaponGraphics = new WeaponGraphics();

	this->Head.delay = this->Body.delay = TROOPER_ANIMATION_DELAY;

	this->setCurrentSpriteFacing(ENTITY_FACING_SOUTH);

	this->setCurrentAnimationState(ENTITY_ANIMATION_IDLE);
	this->_setSpritesToIdle(); //Just in case the idle above didn't hold because of initial shit
	this->_setSouthFacingSpriteValues();
}

void TrooperGraphics::releaseLivingEntityGraphics()
{
	this->_SpriteObj = NULL;

	this->_HeadTexture = NULL;
	this->_BodyTexture = NULL;

	this->_WeaponGraphics->releaseWeaponGraphics();
	this->_WeaponGraphics = NULL;
}

void TrooperGraphics::render()
{
	//Which comes first, head/arms or body, depends on facing
	switch (this->_currentFacing) {

		case ENTITY_FACING_SOUTH:
		case ENTITY_FACING_SOUTHEAST:
		case ENTITY_FACING_SOUTHWEST:
			this->Body.spriteTransformDraw(*this->_BodyTexture, this->_SpriteObj);
			this->Head.spriteTransformDraw(*this->_HeadTexture, this->_SpriteObj);
			this->_WeaponGraphics->render();
			break;
		case ENTITY_FACING_NORTH:
		case ENTITY_FACING_NORTHEAST:
		case ENTITY_FACING_NORTHWEST:
			this->_WeaponGraphics->render();
			this->Head.spriteTransformDraw(*this->_HeadTexture, this->_SpriteObj);
			this->Body.spriteTransformDraw(*this->_BodyTexture, this->_SpriteObj);
			break;
		default:
			this->Body.spriteTransformDraw(*this->_BodyTexture, this->_SpriteObj);
			this->Head.spriteTransformDraw(*this->_HeadTexture, this->_SpriteObj);
			this->_WeaponGraphics->render();
			break;
	}

}

void TrooperGraphics::setCurrentSpriteFacing(int newFacing)
{
	if (this->_currentFacing == newFacing) {
		return;
	}

	this->_currentFacing = newFacing;

	this->_WeaponGraphics->setCurrentSpriteFacing(newFacing);

	switch (newFacing) {

		case ENTITY_FACING_NORTH:
			this->_setNorthFacingSpriteValues();
			break;
		case ENTITY_FACING_SOUTH:
			this->_setSouthFacingSpriteValues();
			break;
		case ENTITY_FACING_EAST:
			this->_setEastFacingSpriteValues();
			break;
		case ENTITY_FACING_WEST:
			this->_setWestFacingSpriteValues();
			break;
		case ENTITY_FACING_SOUTHEAST:
			this->_setMirrorValuesForXAxis(1);
			this->_setSpriteValuesForFacing(TROOPER_SPRITE_ROW_SOUTHEAST);
			break;
		case ENTITY_FACING_SOUTHWEST:
			this->_setMirrorValuesForXAxis(-1);
			this->_setSpriteValuesForFacing(TROOPER_SPRITE_ROW_SOUTHEAST);
			break;
		case ENTITY_FACING_NORTHEAST:
			this->_setMirrorValuesForXAxis(1);
			this->_setSpriteValuesForFacing(TROOPER_SPRITE_ROW_NORTHEAST);
			break;
		case ENTITY_FACING_NORTHWEST:
			this->_setMirrorValuesForXAxis(-1);
			this->_setSpriteValuesForFacing(TROOPER_SPRITE_ROW_NORTHEAST);
			break;
	}

	//To "reset" animations given new sprite row values
	this->setCurrentAnimationState(this->_currentAnimationState);
}

void TrooperGraphics::animate()
{
	/*if (this->_renderBlood) {
		this->_Blood.x = this->positionX;
		this->_Blood.y = this->positionY;
		this->_Blood.animate();
	}*/
	
	/*int bodyOffset = 0;
	if (this->Body.scalingX == -1) {
		bodyOffset = TROOPER_BODY_SPRITE_SIZE_HALF;
	}*/

	//Must subtract so the middle of the sprite is at the position
	//Must compensate for scaling
	short offSet = (short)((1 - this->Body.scalingX * 0.5) * TROOPER_BODY_SPRITE_SIZE_HALF);
	this->Body.x = (float)(this->positionX + offSet);
	this->Body.y = (float)(this->positionY);

	this->Head.x = (float)(this->Body.x + this->_HEAD_OFFSET_X * this->Body.scalingX);
	this->Head.y = (float)(this->Body.y - this->_HEAD_OFFSET_Y);

	this->_WeaponGraphics->MapPosition.x = this->positionX;
	this->_WeaponGraphics->MapPosition.y = this->positionY;

	switch (this->_currentAnimationState) {

		case ENTITY_ANIMATION_RUNNING:
			this->Body.animateWithShakeInYDirection();
			this->Head.animateWithShakeInYDirection();
			this->_WeaponGraphics->animateWithShakeInYDirection();
			break;
		case ENTITY_ANIMATION_ATTACK:
			this->Head.animateWithShakeInYDirection();
			this->Body.animateWithShakeInYDirection();
			this->_WeaponGraphics->animateWithShakeInYDirection();
			break;
		case ENTITY_ANIMATION_IDLE:
			this->Body.animate();
			this->Head.animate();
			this->_WeaponGraphics->animate();
			break;
	}
	
}

void TrooperGraphics::setCurrentAnimationState(int newAnimationState)
{
	//There's a problem here where they switch facings when running (but don't stop running)
	//so the animation doesn't get updated
	/*if (this->_currentAnimationState == newAnimationState) {
		return;
	}*/

	this->_currentAnimationState = newAnimationState;
	switch (newAnimationState) {

		case ENTITY_ANIMATION_IDLE:
			this->_setSpritesToIdle();
			break;
		case ENTITY_ANIMATION_RUNNING:
			this->_setSpritesToRunning();
			break;
		case ENTITY_ANIMATION_ATTACK:
			this->_setSpritesToAttacking();
			break;
		case ENTITY_ANIMATION_DYING:
			switch (this->_currentFacing) {
				case ENTITY_FACING_SOUTHWEST:
				case ENTITY_FACING_WEST:
				case ENTITY_FACING_NORTHWEST:
				case ENTITY_FACING_NORTH:
					this->setCurrentSpriteFacing(ENTITY_FACING_WEST);
					break;
				default:
					this->setCurrentSpriteFacing(ENTITY_FACING_EAST);
					break;
			}
			this->Body.endFrame = this->Body.startFrame = this->Body.frame = TROOPER_SPRITE_ROW_DEATH * TROOPER_BODY_SPRITESHEET_NUM_COLUMNS;
			this->_setSingleFrameSpriteRows(TROOPER_SPRITE_ROW_DEATH);
			this->Body.height = 50;
			this->Body.width = 50;
			this->_HEAD_OFFSET_X = -3;
			this->_HEAD_OFFSET_Y = 15;
			break;
	}
}

//
// Private setters
//


void TrooperGraphics::_setSpritesToIdle()
{
	this->Body.startFrame = this->Body.endFrame = this->_currentSpriteRow * TROOPER_BODY_SPRITESHEET_NUM_COLUMNS;
}


void TrooperGraphics::_setSpritesToRunning()
{
	this->Body.startFrame = this->_currentSpriteRow * TROOPER_BODY_SPRITESHEET_NUM_COLUMNS + TROOPER_BODY_SPRITESHEET_RUNNING_START_FRAME;
	this->Body.endFrame = this->Body.startFrame + TROOPER_BODY_SPRITESHEET_RUNNING_END_FRAME - 1;
}


void TrooperGraphics::_setSpritesToAttacking()
{
	/*this->Body.startFrame = this->_currentSpriteRow * TROOPER_BODY_SPRITESHEET_NUM_COLUMNS;
	this->Body.endFrame = this->Body.startFrame + TROOPER_BODY_SPRITESHEET_ATTACK_END_FRAME;
	this->_HEAD_OFFSET_Y = 6;*/
}


//
// Changing sprite direction
//


void TrooperGraphics::_setNorthFacingSpriteValues()
{
	this->_setMirrorValuesForXAxis(1);
	this->_setSpriteValuesForFacing(TROOPER_SPRITE_ROW_NORTH);
}

void TrooperGraphics::_setSouthFacingSpriteValues()
{
	this->_setMirrorValuesForXAxis(1);
	this->_setSpriteValuesForFacing(TROOPER_SPRITE_ROW_SOUTH);
}

void TrooperGraphics::_setEastFacingSpriteValues()
{
	this->_setMirrorValuesForXAxis(1);
	this->_setSpriteValuesForFacing(TROOPER_SPRITE_ROW_SIDE);
}

void TrooperGraphics::_setWestFacingSpriteValues()
{
	this->_setMirrorValuesForXAxis(-1);
	this->_setSpriteValuesForFacing(TROOPER_SPRITE_ROW_SIDE);
}

void TrooperGraphics::_setSpriteValuesForFacing(int row)
{
	switch (row) 
	{
		case TROOPER_SPRITE_ROW_SOUTH:
			this->_HEAD_OFFSET_X = 7;
			this->_HEAD_OFFSET_Y = 15;
			break;
		case TROOPER_SPRITE_ROW_NORTH:
			this->_HEAD_OFFSET_X = 8;
			this->_HEAD_OFFSET_Y = 15;
			break;
		case TROOPER_SPRITE_ROW_SIDE:
			this->_HEAD_OFFSET_X = 7;
			this->_HEAD_OFFSET_Y = 15;
			break;
		case TROOPER_SPRITE_ROW_SOUTHEAST:
			this->_HEAD_OFFSET_X = 7;
			this->_HEAD_OFFSET_Y = 15;
			break;
		case TROOPER_SPRITE_ROW_NORTHEAST:
			this->_HEAD_OFFSET_X = 8;
			this->_HEAD_OFFSET_Y = 15;
			break;
	}

	this->_currentSpriteRow = row;
	this->_setSingleFrameSpriteRows(this->_currentSpriteRow);

	this->_setSingleFrameSpriteRows(row);
}

void TrooperGraphics::_setMirrorValuesForXAxis(float mirrorValue)
{
	this->Body.scalingX = (float)this->Head.scalingX = mirrorValue;
}

void TrooperGraphics::_setSingleFrameSpriteRows(int row)
{
	this->Head.startFrame = this->Head.endFrame = this->Head.frame = row;
	//this->Body.startFrame = this->Body.endFrame = this->Body.frame = TROOPER_BODY_SPRITESHEET_NUM_COLUMNS * row;
}

