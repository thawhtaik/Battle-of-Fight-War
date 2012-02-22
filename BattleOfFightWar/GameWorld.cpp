#include "GameWorld.h"

GameWorld::GameWorld()
{
}

bool GameWorld::initGameWorld()
{
	WorldMap = Map::Map(16, 12);
	WorldMap.initMapTilePathfindingStats();

	GlobalCursor.initCursor(MapCoordinates(0,0));

	GlobalLivingEntitiesList.releaseLivingEntitiesList();
	GlobalProjectileList.releaseProjectileList();
	GlobalAnimatedEffectsList.releaseAnimatedEffectsList();

	//STRESS TEST OOOOH SHIIIIT PARALYZEDDDD!
	for (int i = 0; i < NUM_ASSHOLES; i++) {
		Trooper* AIDude = new Trooper();

		AIDude->positionX = 100 + i * 25;
		AIDude->positionY = 100 + i * 25;
		AIDude->objectIndex = i;

		//Start = WorldMap.getTileAtPosition(AIDude.positionX, AIDude.positionY)->TileCoordinates;
		//Goal = WorldMap.getTileAtCoordinates(i % 15, i % 11)->TileCoordinates;

		//this->_Path = this->_Pathfinder.getPath(&WorldMap, Start, Goal);
		//AIDude.setCurrentPath(this->_Path);

		GlobalLivingEntitiesList.add(AIDude);
	}

	Player *ThePlayer = new Player();
	ThePlayer->positionX = 60;
	ThePlayer->positionY = 60;
	ThePlayer->objectIndex = GlobalLivingEntitiesList.getSize();
	this->_playerId = ThePlayer->objectIndex;
	GlobalLivingEntitiesList.add(ThePlayer);

	this->_Start = WorldMap.getTileAtCoordinates(0, 0)->TileCoordinates;
	this->_Goal = WorldMap.getTileAtCoordinates(12, 7)->TileCoordinates;

	this->_Path = this->_Pathfinder.getPath(&WorldMap, this->_Start, this->_Goal);

	this->_PathSprite.width = this->_PathSprite.height = 16;
	this->_PathSprite.scalingX = this->_PathSprite.scalingY = 2.0;

	GlobalProjectileList.releaseProjectileList();

	return true;
}

void GameWorld::releaseGameWorld()
{
	this->_Path.clear();

	GlobalLivingEntitiesList.releaseLivingEntitiesList();
	GlobalProjectileList.releaseProjectileList();
	GlobalAnimatedEffectsList.releaseAnimatedEffectsList();

	WorldMap.releaseMap();

	GlobalCursor.releaseCursor();
}

void GameWorld::updateGameWorld()
{
	WorldMap.update();

	/*for (int i = 0; i < (int)this->_Path.size(); i++) {
		int x = this->_Path[i].x * MAP_TILE_SIZE;
		int y = this->_Path[i].y * MAP_TILE_SIZE;

		this->_PathSprite.x = (float)x;
		this->_PathSprite.y = (float) y;
		this->_PathSprite.spriteTransformDraw(GlobalTexturePack.HeadTexture, GlobalDirectXStuff.spriteObj);
	}*/

	this->_updateAllLivingEntityTilePositions();

	for (int i = 0; i < GlobalLivingEntitiesList.getSize(); i++) {
		LivingEntity* CurrentLivingEntity = (LivingEntity*)GlobalLivingEntitiesList.getAtIndex(i);
		CurrentLivingEntity->update();
	}

	Player* ThePlayer = (Player*)GlobalLivingEntitiesList.getAtIndex(this->_playerId);
	ThePlayer->update();

	GlobalProjectileList.update();
	GlobalProjectileList.update();
	GlobalProjectileList.update();

	GlobalAnimatedEffectsList.update();

	this->_clearAllLivingEntityTilePositions();
}


void GameWorld::renderGameWorld()
{
	WorldMap.render();

	for (int i = 0; i < GlobalLivingEntitiesList.getSize(); i++) {
		LivingEntity* CurrentLivingEntity = (LivingEntity*)GlobalLivingEntitiesList.getAtIndex(i);
		CurrentLivingEntity->render();
	}

	GlobalProjectileList.render();

	GlobalAnimatedEffectsList.render();

	GlobalCursor.render();
}


void GameWorld::_updateAllLivingEntityTilePositions()
{
	for (int i = 0; i < GlobalLivingEntitiesList.getSize(); i++) {
		this->_updateLivingEntityTilePosition((LivingEntity*)GlobalLivingEntitiesList.getAtIndex(i), i);
	}

}

void GameWorld::_updateLivingEntityTilePosition(LivingEntity* LivingEntity, int entityIndex)
{
	MapTile *CurrentTile = WorldMap.getTileAtPosition(LivingEntity->positionX, LivingEntity->positionY);

	if (CurrentTile != NULL) {
		CurrentTile->currentLivingEntityIndices.insert(entityIndex);
	}
}

void GameWorld::_clearAllLivingEntityTilePositions()
{
	for (int i = 0; i < GlobalLivingEntitiesList.getSize(); i++) {
		this->_clearLivingEntityTilePosition((LivingEntity*)GlobalLivingEntitiesList.getAtIndex(i), i);
	}
}

void GameWorld::_clearLivingEntityTilePosition(LivingEntity* LivingEntity, int entityIndex)
{
	MapTile *CurrentTile = WorldMap.getTileAtPosition(LivingEntity->positionX, LivingEntity->positionY);

	if (CurrentTile != NULL) {
		CurrentTile->currentLivingEntityIndices.clear();
	}
}

Player* GameWorld::getPlayer()
{
	Player* ThePlayer = (Player*)GlobalLivingEntitiesList.getAtIndex(this->_playerId);

	return ThePlayer;
}