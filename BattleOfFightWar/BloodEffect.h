#ifndef _BLOOD_EFFECT_
#define _BLOOD_EFFECT_

#include "AnimatedEffect.h"

class BloodEffect: public AnimatedEffect
{

	public:

		BloodEffect(MapCoordinates NewPosition);

		void animate();
		void render();

	private:

		Sprite _BloodSprite;
};


#endif