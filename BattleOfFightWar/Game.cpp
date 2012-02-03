#include "Game.h"

Game::Game()
{
	this->_gameOver = false;
	this->_gamePaused = false;

	this->_mapTileX = this->_mapTileY = 0;
	this->_cursorX = this->_cursorY = 0;
}

bool Game::initGame()
{
	if (!this->initGameGraphics()) {
		return false;
	}

	this->_GameWorld.initGameWorld();

	return true;
}

void Game::releaseGame()
{
	this->_GameWorld.releaseGameWorld();
	//Keeping game data vs graphics stuff consistent
	this->releaseGameGraphics();
}

bool Game::initGameGraphics()
{
	srand(time(NULL));

	this->_FontLucidaConsole = GlobalDirectXStuff.makeFont("Lucida Console", 24);

	this->_frameStartTime = timeGetTime();

	//---------------- 3D settings ----------------------------------
	//turn dynamic lighting off and z buffering on
	GlobalDirectXStuff.d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	//this->_DirectXStuff->d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);

	//set direct3d stream to use our custom VertexStruct mode
	//this->_Dx->d3ddev->SetFVF(D3DFVF_MYVERTEX);
	//---------------------------------------------------------------

	//This is kind of important
	GlobalTexturePack = TexturePack::TexturePack();
	GlobalTexturePack.initTexturePack();

	Debugger.print("GameGraphics initiation successful");

	return true;
}

void Game::releaseGameGraphics()
{
	//this->_TexturePack.releaseTexturePack();
	GlobalTexturePack.releaseTexturePack();

	if (this->_FontLucidaConsole) {
		this->_FontLucidaConsole->Release();
		this->_FontLucidaConsole = NULL;
	}

}

void Game::runGame()
{
	this->renderScene();
}

void Game::renderScene()
{
	/*if (!GlobalDirectXStuff.d3ddev) {
		return;
	}*/

	//--------------------------------------------------------------------------------------------------

	//if (timeGetTime() == this->_frameStartTime + 10) {
		//this->_GameWorld.updateGameWorld();
	//}


	if (timeGetTime() > this->_frameStartTime + 14) { //this is apparently approx 60 FPS

		this->_frameStartTime = timeGetTime();

		this->_GameWorld.updateGameWorld();

		GlobalDirectXStuff.clearScene(D3DCOLOR_XRGB(0,0,100));

		if (GlobalDirectXStuff.d3ddev->BeginScene()) {		

			GlobalDirectXStuff.spriteObj->Begin(D3DXSPRITE_ALPHABLEND);			

			std::ostringstream stringStream;
			stringStream << "TROOPERS! \n" << this->_cursorX << "," << this->_cursorY << "\n";
			stringStream << this->_mapTileX << "," << this->_mapTileY << "\n";
			GlobalDirectXStuff.fontPrint(this->_FontLucidaConsole, 0, 0, stringStream.str());


			this->_GameWorld.renderGameWorld();


			GlobalDirectXStuff.spriteObj->End();

			GlobalDirectXStuff.d3ddev->EndScene();
			GlobalDirectXStuff.d3ddev->Present(NULL, NULL, NULL, NULL);
		}
	} //end frame if
}

bool Game::isGameOver()
{
	return this->_gameOver;
}

bool Game::isGamePaused()
{
	return this->_gamePaused;
}

GameWorld* Game::getGameWorld()
{
	return &this->_GameWorld;
}

