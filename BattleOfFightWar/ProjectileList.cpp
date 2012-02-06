#include "ProjectileList.h"

ProjectileList GlobalProjectileList;

ProjectileList::ProjectileList()
{
	this->_Projectiles.clear();
}

void ProjectileList::releaseProjectileList()
{
	for (int i = 0; i < this->_Projectiles.size(); i++) {
		this->_Projectiles.at(i)->releaseProjectile();
		this->_Projectiles.erase(this->_Projectiles.begin() + i);
	}

	this->_Projectiles.clear();
}

void ProjectileList::add(Projectile* NewProjectile)
{
	this->_Projectiles.push_back(NewProjectile);
}

Projectile* ProjectileList::getAtIndex(int projectileIndex)
{
	return this->_Projectiles.at(projectileIndex);
}

int ProjectileList::getSize()
{
	return this->_Projectiles.size();
}


void ProjectileList::removeAtIndex(int projectileIndex)
{
	this->_Projectiles.at(projectileIndex)->releaseProjectile();
	delete this->_Projectiles.at(projectileIndex);
	this->_Projectiles.erase(this->_Projectiles.begin() + projectileIndex); //erases element index+1
}


void ProjectileList::update()
{
	for (int i = 0; i < this->_Projectiles.size(); i++) {
		this->_Projectiles.at(i)->update();

		if (this->_Projectiles.at(i)->isFunctional()) {
			continue;
		}

		this->_Projectiles.at(i)->releaseProjectile();
		delete this->_Projectiles.at(i);
		this->_Projectiles.erase(this->_Projectiles.begin() + i);
	}
}


void ProjectileList::render()
{
	for (int i = 0; i < this->_Projectiles.size(); i++) {
		this->_Projectiles.at(i)->render();
	}
}