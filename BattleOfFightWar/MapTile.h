#ifndef _MAP_TILE_
#define _MAP_TILE_

#include <set>

#include "DirectXStuff.h"
#include "MapCoordinates.h"

const int MAP_TILE_SIZE = 64;
const int MAP_TILE_NUMBER_OF_NEIGHBORS = 8;

//Note that these correspond to the tile number on the sprite sheet
const int TERRAIN_TYPE_GRASS = 0;

class MapTile
{
	public: 
		MapTile();
		MapTile(MapCoordinates NewTileCoordinates, int newTerrainType);
		void releaseMapTile();

		MapCoordinates TileCoordinates;

		int terrainType;

		//Yes these are also path-finding-related but can be used for other things too
		int tileSet;
		float cost;
		bool walkable;
		MapTile* NeighborMapTiles[8];

		//Purely pathfinding (A*-related) variables
		float fCost, gCost;
		bool open, closed;
		MapTile *ParentMapTile;

		set<int> currentLivingEntityIndices;
		
	private:
		
		void _initMapTile();
};

#endif