#ifndef _ANIMATED_EFFECT_CREATOR_
#define _ANIMATED_EFFECT_CREATOR_

#include "AnimatedEffectsList.h"
#include "MapCoordinates.h"


#include "BloodEffect.h"


extern AnimatedEffectsList GlobalAnimatedEffectsList;

class AnimatedEffectCreator
{
	public:
		static void createBleedingEffect(MapCoordinates Position);
};


#endif