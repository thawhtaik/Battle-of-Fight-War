#ifndef _PLAYER_
#define _PLAYER_

#include "Trooper.h"

class Player: public Trooper
{

	public:
		Player();
		Player(LivingEntityGraphics* NewLivingEntityGraphics);

		void update();

	private:
};

#endif