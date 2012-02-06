#include "AnimatedEffectsList.h"

AnimatedEffectsList GlobalAnimatedEffectsList;

AnimatedEffectsList::AnimatedEffectsList()
{
	this->_AnimatedEffects.clear();
}

void AnimatedEffectsList::releaseAnimatedEffectsList()
{
	for (int i = 0; i < this->_AnimatedEffects.size(); i++) {
		delete this->_AnimatedEffects.at(i);
		this->_AnimatedEffects.erase(this->_AnimatedEffects.begin() + i);
	}

	this->_AnimatedEffects.clear();
}


void AnimatedEffectsList::add(AnimatedEffect* NewEffect)
{
	this->_AnimatedEffects.push_back(NewEffect);
}


void AnimatedEffectsList::removeAtIndex(int effectIndex)
{
	delete this->_AnimatedEffects.at(effectIndex);
	this->_AnimatedEffects.erase(this->_AnimatedEffects.begin() + effectIndex); //erases element index+1
}


AnimatedEffect* AnimatedEffectsList::getAtIndex(int effectIndex)
{
	return this->_AnimatedEffects.at(effectIndex);
}


void AnimatedEffectsList::update()
{
	for (int i = 0; i < this->_AnimatedEffects.size(); i++) {
		this->_AnimatedEffects.at(i)->animate();

		if (this->_AnimatedEffects.at(i)->isEffectFinished()) {
			delete this->_AnimatedEffects.at(i);
			this->_AnimatedEffects.erase(this->_AnimatedEffects.begin() + i);
		}
	}
}


void AnimatedEffectsList::render()
{
	for (int i = 0; i < this->_AnimatedEffects.size(); i++) {
		this->_AnimatedEffects.at(i)->render();
	}
}
