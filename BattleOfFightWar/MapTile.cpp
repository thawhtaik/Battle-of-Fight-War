#include "MapTile.h"

MapTile::MapTile()
{
	this->_initMapTile();

	this->terrainType = 0;

	this->currentLivingEntityIndices.clear();
}

MapTile::MapTile(MapCoordinates NewTileCoordinates, int newTerrainType)
{
	this->_initMapTile();

	this->TileCoordinates = NewTileCoordinates;
	this->terrainType = newTerrainType;
}

void MapTile::_initMapTile()
{
	this->open = this->closed = false;
	this->walkable = true;
	this->tileSet = this->cost = this->fCost = this->gCost = 0;

	for (int i = 0; i < MAP_TILE_NUMBER_OF_NEIGHBORS; i++) {
		this->NeighborMapTiles[i] = NULL;
	}

	this->ParentMapTile = NULL;
}

void MapTile::releaseMapTile()
{
	this->ParentMapTile = NULL;

	for (int i = 0; i < MAP_TILE_NUMBER_OF_NEIGHBORS; i++) {
		this->NeighborMapTiles[i] = NULL;
	}

	this->currentLivingEntityIndices.clear();
}