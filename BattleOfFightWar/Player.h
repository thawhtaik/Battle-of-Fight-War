#ifndef _PLAYER_
#define _PLAYER_

#include "Trooper.h"
#include <math.h>

#include <stdio.h>
#include <sstream>

#include "Cursor.h"

extern Cursor GlobalCursor;

class Player: public Trooper
{

	public:
		Player();
		Player(LivingEntityGraphics* NewLivingEntityGraphics);

		void lookAtPosition(MapCoordinates Position);

		void attack();
		void update();

	private:

		void _moveBasedOnCurrentMovementDirection();
};

#endif