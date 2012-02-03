/** Game.h */

#ifndef _GAME_
#define _GAME_

#define TIME_PER_FRAME 0.5 //Number of seconds for a frame of game advancement

/** The main logic of the game; should use all other platform-independent game logic related stuff
*	(except the controller)
*/
#include <time.h>
#include <sstream>
#include <vector>

#include "Debug.h"
#include "DirectXStuff.h"
#include "GameWorld.h"

extern DirectXStuff GlobalDirectXStuff;
extern TexturePack GlobalTexturePack;

class Game
{
	friend class Controller;

    public:

	    Game();
		bool initGame();
		void releaseGame();	

		bool initGameGraphics();
		void releaseGameGraphics();	
		
		void runGame();
		void renderScene();

		//Need these for main since I don't know how to make it a friend
		bool isGameOver();
		bool isGamePaused();

		GameWorld* getGameWorld();

	private:

		GameWorld _GameWorld;

		//Other specific graphics pointers
		LPD3DXFONT _FontLucidaConsole;

		DWORD _frameStartTime;

		long _cursorX;
		long _cursorY;
		int _mapTileX;
		int _mapTileY;

		int screenWidth;
		int screenHeight;

		//Modes and stuff -----------------------------------------------------------------------
		bool _gameOver;
		bool _gamePaused;

};//end class

#endif