#ifndef _ANIMATED_EFFECTS_LIST_
#define _ANIMATED_EFFECTS_LIST_

#include "AnimatedEffect.h"
#include <vector>

class AnimatedEffectsList
{

	public:

		AnimatedEffectsList();
		void releaseAnimatedEffectsList();

		void update();
		void render();

		void add(AnimatedEffect* NewEffect);
		void removeAtIndex(int effectIndex);

		AnimatedEffect* getAtIndex(int projectileIndex);

	private:

		std::vector<AnimatedEffect*> _AnimatedEffects;
};


#endif