#include "MapGraphics.h"

MapGraphics::MapGraphics()
{
	this->_MapSurface = NULL;
}

MapGraphics::MapGraphics(std::vector<MapTile> MapTiles, int newNumberOfTilesX, int newNumberOfTilesY)
{
	this->_createMapSurfaceObject(newNumberOfTilesX, newNumberOfTilesY);

	for (int i = 0; i < MapTiles.size(); i++) {

		MapCoordinates TileCoordinates = MapTiles[i].TileCoordinates;
		int destinationX = TileCoordinates.x * MAP_TILE_SIZE;
		int destinationY = TileCoordinates.y * MAP_TILE_SIZE;
		this->_drawTileToGameMapSurface(GlobalTexturePack.MapTilesSurface, this->_MapSurface, TERRAIN_TYPE_GRASS, destinationX, destinationY);
	}
}

MapGraphics::MapGraphics(int numberOfXTiles, int numberOfYTiles)
{
	this->_createMapSurfaceObject(numberOfXTiles, numberOfYTiles);

	for (int x = 0; x < numberOfXTiles; x++) {
		for (int y = 0; y < numberOfYTiles; y++) {
			int destinationX = x * MAP_TILE_SIZE;
			int destinationY = y * MAP_TILE_SIZE;
			this->_drawTileToGameMapSurface(GlobalTexturePack.MapTilesSurface, this->_MapSurface, TERRAIN_TYPE_GRASS, destinationX, destinationY);
		}
	}
}

bool MapGraphics::_createMapSurfaceObject(int numberOfXTiles, int numberOfYTiles)
{
	int mapWidth = MAP_TILE_SIZE * numberOfXTiles;
	int mapHeight = MAP_TILE_SIZE * numberOfYTiles;

	//Create the scrolling game world bitmap
	HRESULT Result = GlobalDirectXStuff.d3ddev->CreateOffscreenPlainSurface(
		mapWidth, //width of surface
		mapHeight, //height of surface
		D3DFMT_X8R8G8B8, //WTF
		D3DPOOL_DEFAULT, //WTF
		&(this->_MapSurface), //game world surface (note pass by reference, apparently LPDIRECT3DSURFACE9 is not a long pointer)
		NULL
	);

	if (Result != D3D_OK) {
		Debugger.print("Error creating game world surface!");
		return false;
	}

	return true;
}

void MapGraphics::_drawTileToGameMapSurface(
	LPDIRECT3DSURFACE9 SourceSurface,
	LPDIRECT3DSURFACE9 DestinationSurface,
	int tileNumber, //tileNumber on the source sprite sheet; corresponds to terrain type
	int destinationX,  //x coords of where to draw
	int destinationY //y coords of where to draw
) {
	//Create rectangle to describe source surface image
	RECT SourceRectangle;
	//sourceRectangle.left = tileNumber;
	//sourceRectangle.top = tileNumber;
	SourceRectangle.left = (tileNumber % MAP_TILE_SPRITESHEET_NUMBER_OF_COLUMNS) * MAP_TILE_SIZE;
	SourceRectangle.top = (tileNumber / MAP_TILE_SPRITESHEET_NUMBER_OF_COLUMNS) * MAP_TILE_SIZE;
	SourceRectangle.right = SourceRectangle.left + MAP_TILE_SIZE;
	SourceRectangle.bottom = SourceRectangle.top + MAP_TILE_SIZE;

	//Set destination rectangle
	RECT destinationRectangle = {destinationX, destinationY, destinationX + MAP_TILE_SIZE, destinationY + MAP_TILE_SIZE};

	//Actually draw the damn tile
	GlobalDirectXStuff.d3ddev->StretchRect(SourceSurface, &SourceRectangle, DestinationSurface, &destinationRectangle, D3DTEXF_NONE);
}

void MapGraphics::releaseMapGraphics()
{
	if (this->_MapSurface != NULL) {
		this->_MapSurface->Release();
		this->_MapSurface = NULL;
	}

}

void MapGraphics::render()
{
	D3DSURFACE_DESC BackBufferDescription;
	GlobalDirectXStuff.backbuffer->GetDesc(&BackBufferDescription);

	//Calculate how much of the map you can see, then draw it to the back buffer
	//For now just using the back buffer width and height until I implement movable camera
	RECT RectOfGameMapToDrawToScreen = {0, 0, BackBufferDescription.Width, BackBufferDescription.Height};

	RECT DestRectangle = {0, 0, BackBufferDescription.Width, BackBufferDescription.Height};

	GlobalDirectXStuff.d3ddev->StretchRect(
		this->_MapSurface,
		&RectOfGameMapToDrawToScreen,
		GlobalDirectXStuff.backbuffer,
		&DestRectangle,
		D3DTEXF_NONE
	);
}