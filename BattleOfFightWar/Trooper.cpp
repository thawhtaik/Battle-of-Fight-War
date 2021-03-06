#include "Trooper.h"

Trooper::Trooper()
{
	this->sizeX = this->sizeY = TROOPER_BODY_SPRITE_SIZE_HALF;
	
	this->hitboxSizeX = TROOPER_BODY_SPRITE_SIZE_HALF;
	this->hitboxSizeY = 36;

	this->initLivingEntityGraphics();

	this->setCurrentWeapon(WEAPON_TYPE_RIFLE);
}


Trooper::Trooper(TrooperGraphics* NewTrooperGraphics)
{
	this->_EntityGraphics = NULL;
	this->_EntityGraphics = NewTrooperGraphics;
}

void Trooper::initLivingEntityGraphics()
{
	this->_EntityGraphics = new TrooperGraphics;
}


void Trooper::releaseWorldObject()
{
	this->_Brain.releaseBrain();

	delete this->_CurrentGoal;
	this->_CurrentGoal = NULL;

	this->_CurrentPath.clear();
	
	for (int i = 0; i < this->_CurrentActions.size(); i++) {
		this->_CurrentActions.at(i)->releaseAction();
	}
	this->_CurrentActions.clear();

	this->_EntityGraphics->releaseLivingEntityGraphics();
	delete this->_EntityGraphics;
	this->_EntityGraphics = NULL;
	this->_CurrentWeapon = NULL;

	this->_updateFunctionPointer = NULL;
	this->_moveFunctionPointer = NULL;
}

void Trooper::setCurrentPath(std::vector<MapCoordinates> NewPath)
{
	this->_CurrentPath = NewPath;
}


bool Trooper::isPositionInObjectHitbox(MapCoordinates Position)
{
	return !(Position.x > this->positionX + this->hitboxSizeX || Position.x < this->positionX ||		
			Position.y > this->positionY + this->hitboxSizeY  || Position.y < (this->positionY - TROOPER_BODY_SPRITE_SIZE_HALF));
}