/** DirectXStuff.h
    Independent of whatever graphics interface you're using so its supposed to be stay like this.
	A pain in the ass layer on top of more complex shit.  Fuck everything.
*/

#ifndef _DIRECTX_STUFF_
#define _DIRECTX_STUFF_

//most importantly include directx9 header and library
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//For debugging stuff (both of these)
#define D3D_DEBUG_INFO
#include <Dxerr.h>

#include <iostream>

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#include "Sprite.h"

#include "Debug.h"

#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx9d.lib")

//macro to detect key presses;
//#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

using namespace std;

const string APPTITLE = "TROOPERS!";

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const int BACK_BUFFER_WIDTH = 512;
const int BACK_BUFFER_HEIGHT = 384;

enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX}; //colors

class DirectXStuff
{
    public:
		DirectXStuff();

		bool initDirectXStuff(HWND window, int newScreenWidth, int newScreenHeight, bool fullScreen);
		void releaseDirectXStuff();

		LPDIRECT3DSURFACE9 loadSurface(string bitmapName); //Load a bitmap file into a surface; return surface pointer
		LPDIRECT3DTEXTURE9 loadTexture(
			string bitmapName, //Load a texture given the bitmap name, return texture pointer
			D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0) //Note the default value for color
		);

		void clearScene(D3DXCOLOR color);

		LPD3DXSPRITE getNewSpriteObject();

		void spriteTransformDraw( //Draw a transformed sprite (sets a matrix's values, and draws sprite using that matrix)
			LPDIRECT3DTEXTURE9 texture,
			int x,
			int y,
			int frameWidth,
			int frameHeight,
			D3DCOLOR color = D3DCOLOR_XRGB(255,255,255),
			int currentFrame = 0, //Note that this is the first defaulted parameter; omitting the rest, you can draw a single-frame sprite using this function
			int columns = 1,
			float rotation = 0.0f,
			float scaling = 1.0f
		);

		void drawRectangle(int x1, int y1, int x2, int y2, enum color c);
		void drawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source); //Draw surface to screen using stretchRect; specify source and dest surfaces

		void drawTile(
			LPDIRECT3DSURFACE9 source, //source surface image
			int tileNumber, //tileNumber on the spriteSheet
			int tileWidth,
			int tileHeight,
			int columnNumber, //tile column number
			LPDIRECT3DSURFACE9 destination, //destination surface
			int destinationX,  //x coords of where to draw
			int destinationY //y coords of where to draw
		);

		LPD3DXFONT makeFont(
			string fontName, //The name of the font you want
			int fontSize //font size
		);
		void fontPrint(LPD3DXFONT font, int xPos, int yPos, string text, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));

		//3D STUFF -------------------------------------------------------------------------------------------------
		
		void resetWorldMatrix(); //Resets world transformation matrix to identity
		void translateWorldMatrix(float x, float y, float z);
		void setCamera(float x, float y, float z, float xLookAt, float yLookAt, float zLookAt);
		void setPerspective(float fieldOfView, float aspectRatio, float nearRange, float farRange);

		DWORD floatToDWord(float f);

		//3D Model STUFF -------------------------------------------------------------------------------------------

		bool findFile(string *fileName);
		bool doesFileExist(const string &fileName);

		void splitPath(const string &inputPath, string *pathOnly, string *fileNameOnly);

		//public vars
		//D3D object and device pointers
		LPDIRECT3D9 d3d;
        LPDIRECT3DDEVICE9 d3ddev;
		//D3D backbuffer and surface pointers
		LPDIRECT3DSURFACE9 backbuffer;
		LPDIRECT3DSURFACE9 surface;

		//Sprite renderer; handles sprites and includes function to draw sprites from a texture
		//Should probably pass this to fontPrint for use in drawFont (makes it much faster apparently)
		LPD3DXSPRITE spriteObj;

		//Camera location and target
		D3DXVECTOR3 CameraLocation;
		D3DXVECTOR3 CameraTarget;

		//Rectangle for Bitblock transfer
		RECT rect;
};

#endif