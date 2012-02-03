/** Controller.cpp */

#include "Controller.h"

Controller::Controller(Game* newGame)
{
	this->_Game = newGame;
}

void Controller::releaseController()
{
	this->_Game = NULL;
}

bool Controller::isGamePaused()
{
	return _Game->_gamePaused;
}

void Controller::setGamePaused(bool pauseValue)
{
	this->_Game->_gamePaused = pauseValue;
}

void Controller::setGameOver(bool gameOverValue)
{
	this->_Game->_gameOver = gameOverValue;
}

void Controller::updateCursorCoordinates(long x, long y)
{
	this->_Game->_cursorX = x;
	this->_Game->_cursorY = y;
}

void Controller::updateMapTileCoordinates(long x, long y)
{
	this->_Game->_cursorX = x;
	this->_Game->_cursorY = y;

	MapTile* CurrentMousedOverTile = WorldMap.getTileAtPosition((int)x, (int)y);

	if (CurrentMousedOverTile != NULL) {
		this->_Game->_mapTileX = CurrentMousedOverTile->TileCoordinates.x;
		this->_Game->_mapTileY = CurrentMousedOverTile->TileCoordinates.y;
	}
}

void Controller::movePlayer(int direction)
{
	Player* ThePlayer = this->_Game->_GameWorld.getPlayer();
	ThePlayer->setCurrentMovementDirection(direction);
}

void Controller::setPath(long mouseX, long mouseY)
{
	/*MapTile* CurrentMousedOverTile = WorldMap.getTileAtPosition((int)mouseX, (int)mouseY);

	if (CurrentMousedOverTile != NULL) {
		
		MapTile* StartTile = WorldMap.getTileAtPosition(this->_Game->_Player.positionX, this->_Game->_Player.positionY);

		MapCoordinates StartCoordinates = StartTile->TileCoordinates;
		MapCoordinates GoalCoordinates = CurrentMousedOverTile->TileCoordinates;
		
		this->_Game->_Path = this->_Game->_Pathfinder.getPath(&WorldMap, StartCoordinates, GoalCoordinates);

		this->_Game->_Player.setCurrentPath(this->_Game->_Path);
	}*/
}

void Controller::playerAttack()
{
	Player* ThePlayer = this->_Game->_GameWorld.getPlayer();
	ThePlayer->attack();
}