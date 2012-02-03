#include "TexturePack.h"

TexturePack GlobalTexturePack;

TexturePack::TexturePack()
{
	this->HeadTexture = NULL;
	this->BodyTexture = NULL;
	this->LegsTexture = NULL;
}

bool TexturePack::initTexturePack()
{
	Debugger.print("Loading textures");

	this->HeadTexture = GlobalDirectXStuff.loadTexture("Sprites/head.bmp", D3DCOLOR_XRGB(255, 255 , 255));
	if (!this->HeadTexture) {
		Debugger.print("Error loading head spritesheet!");
		return false;
	}

	this->BodyTexture = GlobalDirectXStuff.loadTexture("Sprites/body.bmp", D3DCOLOR_XRGB(255, 255 , 255));
	if (!this->BodyTexture) {
		Debugger.print("Error loading body spritesheet!");
		return false;
	}

	this->LegsTexture = GlobalDirectXStuff.loadTexture("Sprites/legs.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (!this->LegsTexture) {
		Debugger.print("Error loading legs spritesheet!");
		return false;
	}

	this->BloodTexture = GlobalDirectXStuff.loadTexture("Sprites/blood.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (!this->BloodTexture) {
		Debugger.print("Error loading blood spritesheet!");
		return false;
	}

	this->RifleTexture = GlobalDirectXStuff.loadTexture("Sprites/rifle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (!this->RifleTexture) {
		Debugger.print("Error loading rifle spritesheet!");
		return false;
	}

	this->MuzzleFlashTexture = GlobalDirectXStuff.loadTexture("Sprites/muzzleflash.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (!this->MuzzleFlashTexture) {
		Debugger.print("Error loading muzzle flash spritesheet!");
		return false;
	}

	this->BulletTexture = GlobalDirectXStuff.loadTexture("Sprites/bullet.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (!this->BulletTexture) {
		Debugger.print("Error loading bullet spritesheet!");
		return false;
	}

	this->MapTilesSurface = GlobalDirectXStuff.loadSurface("Sprites/maptiles.bmp");
	if (!this->MapTilesSurface) {
		Debugger.print("Error loading map tile spritesheet!");
		return false;
	}

	Debugger.print("Textures loaded");
	return true;
}

void TexturePack::releaseTexturePack()
{
	if (this->HeadTexture != NULL) {
		this->HeadTexture->Release();
	}
	if (this->BodyTexture != NULL) {
		this->BodyTexture->Release();
	}
	if (this->LegsTexture != NULL) {
		this->LegsTexture->Release();
	}
	if (this->RifleTexture != NULL) {
		this->RifleTexture->Release();
	}
	if (this->MuzzleFlashTexture != NULL) {
		this->MuzzleFlashTexture->Release();
	}
	if (this->BulletTexture != NULL) {
		this->BulletTexture->Release();
	}
	if (this->MapTilesSurface != NULL) {
		this->MapTilesSurface->Release();
	}

}