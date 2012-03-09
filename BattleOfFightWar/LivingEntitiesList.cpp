#include "LivingEntitiesList.h"

LivingEntitiesList GlobalLivingEntitiesList;

LivingEntitiesList::LivingEntitiesList()
{
	this->_LivingEntities.clear();
}

void LivingEntitiesList::releaseLivingEntitiesList()
{
	for (int i = 0; i < this->_LivingEntities.size(); i++) {
		this->_LivingEntities.at(i)->releaseWorldObject();
		delete this->_LivingEntities.at(i);
		this->_LivingEntities.erase(this->_LivingEntities.begin() + i);
	}

	this->_LivingEntities.clear();
}


void LivingEntitiesList::removeAtIndex(int livingEntityIndexIndex)
{
	this->_LivingEntities.at(livingEntityIndexIndex)->releaseWorldObject();
	delete this->_LivingEntities.at(livingEntityIndexIndex);

	this->_LivingEntities.erase(this->_LivingEntities.begin() + livingEntityIndexIndex); //erases element index+1
}


void LivingEntitiesList::add(WorldObject* NewLivingEntity)
{
	this->_LivingEntities.push_back(NewLivingEntity);
}

WorldObject* LivingEntitiesList::getAtIndex(int livingEntityIndex)
{
	return this->_LivingEntities.at(livingEntityIndex);
}

int LivingEntitiesList::getSize()
{
	return this->_LivingEntities.size();
}