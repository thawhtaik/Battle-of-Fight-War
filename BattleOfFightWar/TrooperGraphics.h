#ifndef _TROOPER_GRAPHICS_
#define _TROOPER_GRAPHICS_

#include <cmath>
#include "LivingEntityGraphics.h"

#define TROOPER_HEAD_SPRITESHEET_NUM_COLUMNS 1
#define TROOPER_ARMS_SPRITESHEET_NUM_COLUMNS 1
#define TROOPER_BODY_SPRITESHEET_NUM_COLUMNS 5

#define TROOPER_BODY_SPRITESHEET_RUNNING_START_FRAME 1
#define TROOPER_BODY_SPRITESHEET_RUNNING_END_FRAME 4

#define TROOPER_BODY_SPRITESHEET_ATTACK_START_FRAME 1
#define TROOPER_BODY_SPRITESHEET_ATTACK_END_FRAME 4

#define TROOPER_SPRITE_ROW_SOUTH 0
#define TROOPER_SPRITE_ROW_NORTH 1
#define TROOPER_SPRITE_ROW_SIDE 2

class TrooperGraphics: public LivingEntityGraphics
{
	public:

		TrooperGraphics();

		void releaseLivingEntityGraphics();

		void render();
		void animate();

		void setCurrentSpriteFacing(int newFacing);
		void setCurrentAnimationState(int newAnimationState);

	private:

		void _initTrooperGraphics();

		short _currentFacing;

		int _currentSpriteRow;
		int _currentAnimationState;

		void _setNorthFacingSpriteValues();
		void _setSouthFacingSpriteValues();
		void _setEastFacingSpriteValues();
		void _setWestFacingSpriteValues();

		void _setSpriteValuesForFacing(int row);

		void _setMirrorValuesForXAxis(float mirrorValue);
		void _setSingleFrameSpriteRows(int row);

		int _HEAD_OFFSET_X;
		int _HEAD_OFFSET_Y;

		void _setSpritesToIdle();
		void _setSpritesToRunning();
		void _setSpritesToAttacking();

		LPDIRECT3DTEXTURE9* _HeadTexture;
		LPDIRECT3DTEXTURE9* _BodyTexture;

		Sprite Head;
		Sprite Body;
};

#endif