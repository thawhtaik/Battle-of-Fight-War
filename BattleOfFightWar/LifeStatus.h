#ifndef _LIFE_STATUS
#define _LIFE_STATUS

#include <Windows.h> //For timeGetTime()

class LifeStatus{

	public:

		LifeStatus();

		void update();

		void damage(int subtractHitPoints);

		int sightRange;
		float hitPoints;

};

#endif