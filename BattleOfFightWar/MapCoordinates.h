#ifndef _MAP_COORDINATES_
#define _MAP_COORDINATES_

class MapCoordinates
{
	public:
		MapCoordinates();
		MapCoordinates(int newX, int newY);

		int x, y;

		bool operator==(const MapCoordinates OtherCoordinates);
		bool operator!=(const MapCoordinates OtherCoordinates);
};

#endif