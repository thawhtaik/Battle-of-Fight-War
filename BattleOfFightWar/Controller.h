/** Controller.h */

#ifndef _CONTROLLER_
#define _CONTROLLER_

#include "Game.h"

/** So the controller manipulates the game */

extern Map WorldMap;

class Controller 
{
    public:

		Controller(Game* NewGame);
		void releaseController();

		bool isGamePaused();

		void setGameOver(bool gameOverValue);
		void setGamePaused(bool pauseValue);

		void updateCursorCoordinates(long x, long y);
		void updateMapTileCoordinates(long x, long y);

		void movePlayer(int direction);
		void setPath(long mouseX, long mouseY);
		void playerAttack();

    private:

		Game* _Game;
		
		bool _paused;

};

#endif