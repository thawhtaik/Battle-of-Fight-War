#include "Sprite.h"

Sprite::Sprite(
		int newFrame,
		int newColumns,
		int newWidth,
		int newHeight,
		D3DCOLOR newColor,
		float newScalingX,
		float newScalingY,
		float newRotation,
		int newStartFrame,
		int newEndFrame,
		int newDirection,
		int newStartTime,
		int newDelay,
		float newVelX,
		float newVelY
) {
	this->frame = newFrame;
	this->columns = newColumns;
	this->width = newWidth;
	this->height = newHeight;
	this->color = newColor;
	this->scalingX = newScalingX;
	this->scalingY = newScalingY;
	this->rotation = newRotation;
	this->startFrame = newStartFrame;
	this->endFrame = newEndFrame;
	this->direction = newDirection;
	this->startTime = newStartTime;
	this->delay = newDelay;
	this->velX = newVelX;
	this->velY = newVelY;

	this->yShakeOffset = 1;
}

/** Update the frame number and game timer (passed by reference); frame number only changes once "delay" amount of time has passed
*   start and end frame refer to the numbers of the starting and ending frames in the sprite sheet
    direction is how much the current frame should increment per animation (either - or +)
	starttime is the starting time of the current frame (so it's reset every frame)
*/
void Sprite::animate()
{
	if ((int)GetTickCount() > this->startTime + this->delay) //has 1 frame passed? (time per frame defined by delay)
	{
		this->startTime = GetTickCount(); //set new start point

		this->frame += this->direction; //direction does not necessarily have to be 1
		
		//make sure frame stays within bounds, whether its going forwards or backwards
		if (frame > this->endFrame) {
			frame = this->startFrame;
		} else if (frame < this->startFrame) {
			frame = this->endFrame;
		}
	}
}

void Sprite::animateWithShakeInYDirection()
{
	if ((int)GetTickCount() > this->startTime + this->delay)
	{
		this->startTime = GetTickCount();

		this->frame += this->direction;

		this->yShakeOffset *= -1;
		this->y += this->yShakeOffset;
		
		if (frame > this->endFrame) {
			frame = this->startFrame;
		} else if (frame < this->startFrame) {
			frame = this->endFrame;
		}
	}
}

/** Draw a transformed sprite; does all the matrix shit for you */
void Sprite::spriteTransformDraw(LPDIRECT3DTEXTURE9 texture, LPD3DXSPRITE SpriteObj) 
{
	//Create 2D vectors for scale and translate values (indicate scale x-wise and y-wise)
	D3DXVECTOR2 scale(this->scalingX, this->scalingY);
	D3DXVECTOR2 translate(x, y);

	//Set center by dividing width and height by 2, take scaling into account
	D3DXVECTOR2 center((double)(this->width * this->scalingX)/2, (double)(this->height * this->scalingY)/2);

	//The 2D transformation matrix and the function that actually sets the matrix values
	D3DXMATRIX mat;

	D3DXMatrixTransformation2D(
		&mat, //The matrix; note pass by reference 
		NULL, //scaling center point (not used)
		0, //scaling rotation value (not used)
		&scale, //scaling vector
		&center, //rotation / pivot center
		rotation, //rotation angle in RADIANS
		&translate //translation vector
	); 

	//Tell sprite object to use the matrix
	SpriteObj->SetTransform(&mat);

	//calculate frame location in source image (only useful if it's a spritesheet)
	int fx = (this->frame % columns) * this->width;
	int fy = (this->frame / columns) * this->height;
	RECT sourceRect = {fx, fy, fx + this->width, fy + this->height};

	//Draw the sprite frame; note we are not filling in pivot center or position because those are already set 
	//by the matrix
	SpriteObj->Draw(texture, &sourceRect, NULL, NULL, this->color);

	/** More on spriteObj->Draw
	pSrcTexture - a pointer to the texture to be used, see textures
	pSrcRect - pointer to a rectangle defining the area of the texture to use or NULL for the whole texture
	pCenter- pointer to a 3D vector specifying the position in the sprite around which it can be rotated or 
		NULL for top left
	pPosition - pointer to a 3D vector defining the screen position of the sprite. Note: in Direct3D 0,0 
		is the top left of the screen.
	Color - colour value that can be used to modulate the texture colours. A value of 0xFFFFFFFF maintains 
		the colour from the texture. Note: you can use the D3DCOLOR_COLORVALUE macro to create a D3DCOLOR 
		from RGB values.
	*/

}//end spriteTransformDraw