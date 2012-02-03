#include "SearchForThreats.h"

SearchForThreats::SearchForThreats(ActionUser* ActionUser)
{
	this->_ActionUser = ActionUser;
	this->targetPositionX = this->targetPositionY = -1;
	this->_Map = &WorldMap;
}

void SearchForThreats::search()
{
	int positionX = this->_ActionUser->getPositionX();
	int positionY = this->_ActionUser->getPositionY();

	MapTile* CurrentTile = this->_Map->getTileAtPosition(positionX, positionY);
	MapCoordinates CurrentCoordinates = CurrentTile->TileCoordinates;

	LifeStatus* UserLifeStatus = this->_ActionUser->getLifeStatus();
	int sightRange = UserLifeStatus->sightRange;

	int startX, startY, sizeX, sizeY;
	startX = startY = sizeX = sizeY = 0;
	switch (this->_ActionUser->getFacing()) {

		case ENTITY_FACING_SOUTH:
			startX = CurrentCoordinates.x - sightRange;
			startY = CurrentCoordinates.y;
			sizeX = sightRange * 2 + 1;
			sizeY = sightRange + 1;
			break;
		case ENTITY_FACING_NORTH:
			startX = CurrentCoordinates.x - sightRange;
			startY = CurrentCoordinates.y - sightRange;
			sizeX = sightRange * 2 + 1;
			sizeY = sightRange + 1;
			break;
		case ENTITY_FACING_EAST:
			startX = CurrentCoordinates.x;
			startY = CurrentCoordinates.y - sightRange;
			sizeX = sightRange + 1;
			sizeY = sightRange * 2 + 1;
			break;
		case ENTITY_FACING_WEST:
			startX = CurrentCoordinates.x - sightRange;
			startY = CurrentCoordinates.y - sightRange;
			sizeX = sightRange + 1;
			sizeY = sightRange * 2 + 1;
			break;
		default:
			break;
	}

	for (int x = startX; x < startX + sizeX; x++) {
		for (int y = startY; y < startY + sizeY; y++) {

			MapTile* VisibleTile = this->_Map->getTileAtCoordinates(x, y);
			if (VisibleTile != NULL) {

				//Sprite VisibleTileSprite;
				//VisibleTileSprite.width = VisibleTileSprite.height = 16;
				//VisibleTileSprite.scalingX = VisibleTileSprite.scalingY = 2.0;

				//VisibleTileSprite.x = (float)(x * MAP_TILE_SIZE);
				//VisibleTileSprite.y = (float)(y * MAP_TILE_SIZE);
				//VisibleTileSprite.spriteTransformDraw(GlobalTexturePack.HeadTexture, GlobalDirectXStuff.spriteObj);
			}
		}
	}

}