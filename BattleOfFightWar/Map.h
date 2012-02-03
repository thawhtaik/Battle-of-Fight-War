#ifndef _MAP_
#define _MAP_

#include "TexturePack.h"
#include "MapTile.h"

#include <vector>
#include "MapGraphics.h"


class Map
{
	public:
		Map();
		Map(int newNumberOfTilesX, int newNumberOfTilesY);

		void initMapTilePathfindingStats();

		MapTile* getTileAtCoordinates(int x, int y); //Get the real-deal tile
		MapTile* getTileAtPosition(int x, int y);
		bool coordinatesAreWithinMap(MapCoordinates GivenCoordinates);

		void releaseMap();

		void update();
		void render();

		int numberOfTilesX, numberOfTilesY;

		std::vector<MapTile> MapTiles;

	private:

		void _initTiles();
		void _setMapTileNeighbors(MapTile* GivenMapTile);

		void _initTileSets();

		MapGraphics _MapGraphics;
	
};

#endif