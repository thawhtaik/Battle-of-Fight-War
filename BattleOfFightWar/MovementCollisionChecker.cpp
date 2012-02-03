#include "MovementCollisionChecker.h"

MovementCollisionChecker::MovementCollisionChecker()
{	
}


bool MovementCollisionChecker::isLivingEntityInPosition(MapCoordinates Position, int sizeX, int sizeY, int objectIndex)
{
	MapTile* Tile = WorldMap.getTileAtPosition(Position.x, Position.y);
	if (Tile == NULL) {
		return false;
	}
	MapCoordinates TileCoordinates = Tile->TileCoordinates;

	MapTile* TilesToCheckForCollision[9];
	int surroundingTilesIndex = 0;

	for (int i = 0; i < 8; i++) {
		MapTile* NeighborTile = Tile->NeighborMapTiles[i];
		if (NeighborTile != NULL && NeighborTile->walkable) {
			TilesToCheckForCollision[surroundingTilesIndex] = NeighborTile;
			surroundingTilesIndex++;
		}
	}
	//Don't forget our starting tile too!
	TilesToCheckForCollision[surroundingTilesIndex] = Tile;
	surroundingTilesIndex++;

	int bottomRightX = Position.x + sizeX;
	int bottomRightY = Position.y + sizeY;

	for (int i = 0; i < surroundingTilesIndex; i++) {

		set<int> tileLivingEntityIndices = TilesToCheckForCollision[i]->currentLivingEntityIndices;

		set<int>::iterator setIterator;

		for (setIterator = tileLivingEntityIndices.begin(); setIterator != tileLivingEntityIndices.end(); setIterator++) {

			int livingEntityIndex = *setIterator;

			if (livingEntityIndex == objectIndex) {
				continue;
			}

			WorldObject* LivingEntity = GlobalLivingEntitiesList.getAtIndex(livingEntityIndex);

			if (!(Position.x > LivingEntity->positionX + LivingEntity->sizeX || bottomRightX < LivingEntity->positionX ||		
				Position.y > LivingEntity->positionY + LivingEntity->sizeY || bottomRightY < LivingEntity->positionY)
			) {
				return true;
			}
		}
	}

	return false;
}