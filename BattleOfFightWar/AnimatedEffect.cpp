#include "AnimatedEffect.h"

AnimatedEffect::AnimatedEffect()
{
	this->_finished = false;
}

bool AnimatedEffect::isEffectFinished()
{
	return this->_finished;
}