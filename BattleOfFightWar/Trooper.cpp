#include "Trooper.h"

Trooper::Trooper()
{
	this->sizeX = this->sizeY = TROOPER_BODY_SPRITE_SIZE_HALF;

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

	this->_EntityGraphics->releaseLivingEntityGraphics();
	delete this->_EntityGraphics;
	this->_EntityGraphics = NULL;
	this->_CurrentWeapon = NULL;
}

void Trooper::setCurrentPath(std::vector<MapCoordinates> NewPath)
{
	this->_CurrentPath = NewPath;
}