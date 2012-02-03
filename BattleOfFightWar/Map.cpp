#include "Map.h"

Map WorldMap;

Map::Map()
{
	this->numberOfTilesX = this->numberOfTilesY = 0;
}

Map::Map(int newNumberOfTilesX, int newNumberOfTilesY)
{
	this->numberOfTilesX = newNumberOfTilesX;
	this->numberOfTilesY = newNumberOfTilesY;

	this->_initTiles();

	this->_MapGraphics = MapGraphics::MapGraphics(this->MapTiles, this->numberOfTilesX, this->numberOfTilesY);
}

void Map::_initTiles()
{
	for (int y = 0; y < this->numberOfTilesY; y++) {
		for (int x = 0; x < this->numberOfTilesX; x++) {
			MapCoordinates TileCoordinates = MapCoordinates::MapCoordinates(x, y); 
			this->MapTiles.push_back(MapTile::MapTile(TileCoordinates, TERRAIN_TYPE_GRASS));
		}
	}
}

void Map::initMapTilePathfindingStats()
{
	for (int y = 0; y < this->numberOfTilesY; y++) {
		for (int x = 0; x < this->numberOfTilesX; x++) {
			MapTile* CurrentTile = this->getTileAtCoordinates(x, y);

			if (CurrentTile != NULL) {

				CurrentTile->cost = (float)(CurrentTile->terrainType);
				CurrentTile->walkable = true;

				this->_setMapTileNeighbors(CurrentTile);
			}
		}
	}

	this->_initTileSets();
}

void Map::_setMapTileNeighbors(MapTile *GivenMapTile)
{

	//Clear old connections
	for(int i = 0; i < 8; i++) {
		GivenMapTile->NeighborMapTiles[i] = NULL;
	}

	int x = GivenMapTile->TileCoordinates.x;
	int y = GivenMapTile->TileCoordinates.y;

	//Possible neighbors' (8) positions
	MapCoordinates NeighborCoordinates[] = {
		MapCoordinates(x-1, y-1),
		MapCoordinates(x, y-1),
		MapCoordinates(x+1, y-1),
		MapCoordinates(x-1, y),
		MapCoordinates(x+1, y),
		MapCoordinates(x-1, y+1), 
		MapCoordinates(x, y+1),
		MapCoordinates(x+1, y+1)
	};

	int numberOfNeighbors = 0;

	//For each neighbor
	for (int i = 0 ; i < 8; i++) {	

		if (this->coordinatesAreWithinMap(NeighborCoordinates[i])) {
					
			MapTile *Neighbor = this->getTileAtCoordinates(NeighborCoordinates[i].x, NeighborCoordinates[i].y);

			if (Neighbor != NULL && Neighbor->walkable) {
				GivenMapTile->NeighborMapTiles[i] = Neighbor;
			}
		}
	}//end for
}

void Map::_initTileSets()
{
	try {
		int setNumber = 0;
		for (int y = 0; y < this->numberOfTilesY; y++) { //Set a unique tileSet for each tile...
			for (int x = 0;x < this->numberOfTilesX; x++) {
				this->MapTiles[x + y * this->numberOfTilesX].tileSet = setNumber;
				setNumber++;
			}
		}

		bool changed = true;
		while (changed) {
			changed = false;

			//Go through all tiles and see if there's any whose sets should match walkable neighbors with
			//lower-numbered sets.  If any tiles' sets have changed, go through the process again
			for (int y = 0; y < this->numberOfTilesY; y++) {
				for (int x = 0; x < this->numberOfTilesX; x++) {
					MapTile *Tile = this->getTileAtCoordinates(x, y);

					//Find the lowest tileSet of all neighbors this tile can walk to and use that
					if (Tile!= NULL && Tile->walkable) {
						for (int i = 0; i < 8; i++) {
							if (Tile->NeighborMapTiles[i] != NULL &&
								Tile->NeighborMapTiles[i]->walkable &&
								Tile->NeighborMapTiles[i]->tileSet < Tile->tileSet
							) {
								changed = true;
								Tile->tileSet = Tile->NeighborMapTiles[i]->tileSet;
							}
						}
					}
				}
			}//end outer for
		}
	} catch (...) {
		Debugger.print("Error in createTileSets");
	}
}

void Map::releaseMap()
{
	this->_MapGraphics.releaseMapGraphics();

	for (int i = 0; i < this->MapTiles.size(); i++) {
		this->MapTiles[i].releaseMapTile();
	}
	this->MapTiles.clear();
}

//Get the real-deal tile
MapTile* Map::getTileAtCoordinates(int x, int y)
{
	MapCoordinates Coordinates = MapCoordinates::MapCoordinates(x, y);
	if (this->coordinatesAreWithinMap(Coordinates)) {
		return &this->MapTiles[x + y * this->numberOfTilesX]; 
	}

	return NULL;
}

MapTile* Map::getTileAtPosition(int x, int y)
{
	int coordinateX = x / MAP_TILE_SIZE;
	int coordinateY = y / MAP_TILE_SIZE;
	MapCoordinates Coordinates = MapCoordinates::MapCoordinates(coordinateX, coordinateY);
	if (this->coordinatesAreWithinMap(Coordinates)) {
		return &this->MapTiles[coordinateX + coordinateY * this->numberOfTilesX]; 
	}

	return NULL;
}

bool Map::coordinatesAreWithinMap(MapCoordinates GivenCoordinates)
{
	if (
		GivenCoordinates.x < 0 || GivenCoordinates.x >= this->numberOfTilesX ||
		GivenCoordinates.y < 0 || GivenCoordinates.y >= this->numberOfTilesY
	) {
		return false;
	}

	return true;
}

void Map::update()
{
	for (int y = 0; y < this->numberOfTilesY; y++) {
		for (int x = 0; x < this->numberOfTilesX; x++) {
			MapTile *Tile = this->getTileAtCoordinates(x, y);
			Tile->currentLivingEntityIndices.clear();
		}
	}//end outer for
}

void Map::render()
{
	this->_MapGraphics.render();
}

