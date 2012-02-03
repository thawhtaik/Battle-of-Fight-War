#ifndef _MAP_GRAPHICS_
#define _MAP_GRAPHICS_

#include <vector>

#include "MapTile.h"
#include "TexturePack.h"

const int MAP_TILE_SPRITESHEET_NUMBER_OF_COLUMNS = 1;

extern TexturePack GlobalTexturePack;
extern DirectXStuff GlobalDirectXStuff;

class MapGraphics
{
	public:
		MapGraphics();
		MapGraphics(std::vector<MapTile> MapTiles, int newNumberOfTilesX, int newNumberOfTilesY);
		MapGraphics(int newNumberOfTilesX, int newNumberOfTilesY);

		void releaseMapGraphics();

		void render();
		void animate();

		private:

		bool _createMapSurfaceObject(int numberOfXTiles, int numberOfYTiles);
		void _drawTileToGameMapSurface(
			LPDIRECT3DSURFACE9 SourceSurface,
			LPDIRECT3DSURFACE9 DestinationSurface,
			int tileNumber, //tileNumber on the source sprite sheet
			int destinationX,  //x coords of where to draw
			int destinationY //y coords of where to draw
		);

		LPDIRECT3DSURFACE9 _MapSurface;
};

#endif