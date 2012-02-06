#include "AnimatedEffectCreator.h"

void AnimatedEffectCreator::createBleedingEffect(MapCoordinates Position)
{
	BloodEffect* Blood = new BloodEffect(Position);
	GlobalAnimatedEffectsList.add(Blood);
}