#ifndef _SPRITE_
#define _SPRITE_

#include <d3d9.h>
#include <d3dx9.h>

#include "AllConstants.h"

#define SPRITE_FACING_NORTH 0
#define SPRITE_FACING_SOUTH 1
#define SPRITE_FACING_EAST 2
#define SPRITE_FACING_WEST 3

#define SPRITE_SIZE SMALL 16
#define SPRITE_SIZE_MEDIUM 32
#define SPRITE_SIZE_LARGE 64

struct Sprite
{
	Sprite(
		int newFrame = 0,
		int newColumns = 1,
		int newWidth = 0,
		int newHeight = 0,
		D3DCOLOR newColor = D3DCOLOR_XRGB(255, 255, 255),
		float newScalingX = 1.0f,
		float newScalingY = 1.0f,
		float newRotation = 0.0f,
		int newStartFrame = 0,
		int newEndFrame = 0,
		int newDirection = 1,
		int newStartTime = 0,
		int newDelay = 0,
		float newVelX = 0.0f,
		float newVelY = 0.0f
	);

	void animateWithShakeInYDirection();
	void animate();

	void spriteTransformDraw(LPDIRECT3DTEXTURE9 texture, LPD3DXSPRITE SpriteObj);

	//Assload of Sprite variables --------------------------------------------------------------------

	float x,y; //position
	int width, height; //width, height of sprite duh

	int frame, columns; //current frame and # columns; best to not change frame and just let animation handle it

	float scalingX, scalingY, rotation; //for transforms; rotation is in RADIANS

	int startFrame, endFrame; //for spritesheet
	int startTime, delay; //note that starttime is updated as it's passed through animation function

	int direction; //which way and how much the frame updates in the spritesheet

	float velX, velY; //velocity?

	D3DCOLOR color; //tint or sommat

	int yShakeOffset; //How much to shake in y direction
	
};

#endif