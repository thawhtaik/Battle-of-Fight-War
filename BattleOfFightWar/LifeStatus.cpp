#include "LifeStatus.h"

LifeStatus::LifeStatus()
{
	this->sightRange = 2;
	this->hitPoints = 100.0;
}

void LifeStatus::update()
{
}

void LifeStatus::damage(int subtractHitPoints)
{
	this->hitPoints -= subtractHitPoints;
}
