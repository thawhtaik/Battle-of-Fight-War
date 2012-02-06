#ifndef _ANIMATED_EFFECT
#define _ANIMATED_EFFECT

#include "TexturePack.h"
#include "Sprite.h"

#include "MapCoordinates.h"


extern DirectXStuff GlobalDirectXStuff;
extern TexturePack GlobalTexturePack;

class AnimatedEffect
{
	public:

		AnimatedEffect();

		virtual void animate() = 0;
		virtual void render() = 0;

		bool isEffectFinished();

	protected:

		bool _finished;

		MapCoordinates _Position;

};

#endif