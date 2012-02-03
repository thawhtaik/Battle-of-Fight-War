#include "MapCoordinates.h"

MapCoordinates::MapCoordinates()
{
	this->x = this->y = 0;
}

MapCoordinates::MapCoordinates(int newX, int newY)
{
	this->x = newX;
	this->y = newY;
}

bool MapCoordinates::operator==(const MapCoordinates OtherCoordinates)
{
	if ((this->x == OtherCoordinates.x) && (this->y == OtherCoordinates.y)) {
		return true;
	} 

	return false;
}

bool MapCoordinates::operator!=(const MapCoordinates OtherCoordinates)
{
	if ((this->x != OtherCoordinates.x) || (this->y != OtherCoordinates.y)) {
		return true;
	} 
	
	return false;
}