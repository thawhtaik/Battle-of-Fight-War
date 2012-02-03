#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
}

std::vector<MapCoordinates> Pathfinder::getPath(Map *Map, MapCoordinates Start, MapCoordinates Goal)
{
	try {
		//First do some preliminary checks to make sure we're not wasting our time; return empty vectors if there's
		//no possible path
		//Check that the two points are within the bounds of the map // legitimate tiles
		MapTile *StartTile = Map->getTileAtCoordinates(Start.x, Start.y);
		MapTile *GoalTile = Map->getTileAtCoordinates(Goal.x, Goal.y);

		if (!Map->coordinatesAreWithinMap(Start) || !Map->coordinatesAreWithinMap(Goal) || 
			Start == Goal || StartTile == NULL || GoalTile == NULL) {
			return std::vector<MapCoordinates>();
		}
		//Check if a path even exists by comparing sets
		if (!StartTile->walkable || !GoalTile->walkable || StartTile->tileSet != GoalTile->tileSet) {
			return std::vector<MapCoordinates>();
		}
		
		//Time to start our search; use long because we could be dealing with a shitload of tiles here
		long totalNumberOfTiles = Map->numberOfTilesX * Map->numberOfTilesY;

		//Clear all tiles' F and G values and reset open / closed list statuses (they start off in neither list)
		for (long l = 0; l < totalNumberOfTiles; l++) {
			Map->MapTiles[l].fCost = Map->MapTiles[l].gCost = FLT_MAX; //Max float value
			Map->MapTiles[l].open = Map->MapTiles[l].closed = false;
		}

		std::vector<MapTile*> OpenList; //Tiles to be considered for search

		StartTile->gCost = 0;	//Init our starting point (SP)
		StartTile->fCost = Pathfinder::_getDistanceBetweenPoints(Start, Goal);
		StartTile->open = true;

		OpenList.push_back(StartTile);	 //Add StartingTile to the Open list

		//Search as long as there are more tiles to search
		while(!OpenList.empty()) {
			
			MapTile * BestTile = OpenList[0];
			int bestPlace = 0;
			for(int i = 1; i < (int)OpenList.size();i++) //Go through all of OpenList and pick lowest F
				if (OpenList[i]->fCost < BestTile->fCost) { //Remember our starting F's were high as hell before we tileSet them
					BestTile = OpenList[i];
					bestPlace = i;
				}
			
			if (BestTile == NULL) {
				break;			//No path found
			}

			//Best tile is being searched for its worthiness, so no longer in open list
			OpenList[bestPlace]->open = false;
			// Take the best node out of the Open list
			OpenList.erase(OpenList.begin() + bestPlace);
			//The best tile is now being searched, add it to the Closed list
			BestTile->closed = true;

			if (BestTile->TileCoordinates == Goal) { //If the goal has been found
				std::vector<MapCoordinates> PathBackToStart, PathForUnitToFollow;
				MapTile *CurrentTile= BestTile;

				while(CurrentTile->TileCoordinates != Start) {	//Generate path
					PathBackToStart.push_back(CurrentTile->TileCoordinates);
					CurrentTile = CurrentTile->ParentMapTile; //Making our way back
				}

				for (int i = (int)PathBackToStart.size() - 1; i != 0; i--) { 	//Reverse path
					PathForUnitToFollow.push_back(PathBackToStart[i]);
				}
				PathForUnitToFollow.push_back(Goal);
				return PathForUnitToFollow;
			} else {
				// Generate new G and F values for the neighbors
				float newG = BestTile->gCost + 1.0f; //Remember we started at a G value of 0

				for (int i = 0; i < 8; i++) { // otherwise, check each of the neighbors of the Best Tile
					if (BestTile->NeighborMapTiles[i] != NULL) {
						
						//I don't fucking want anything to do with closed tiles; they've already been searched
						if (BestTile->NeighborMapTiles[i]->closed) {
							continue;
						}

						float distanceBetweenTiles = Pathfinder::_getDistanceBetweenPoints(BestTile->TileCoordinates, BestTile->NeighborMapTiles[i]->TileCoordinates);
						float distanceToGoal = Pathfinder::_getDistanceBetweenPoints(BestTile->NeighborMapTiles[i]->TileCoordinates, Goal);
						float newF = G_WEIGHT * newG //Could just be G + distance, but I guess he's added some extra shit for accuracy
							+ H_WEIGHT * distanceToGoal
							+ BestTile->NeighborMapTiles[i]->cost * COST_WEIGHT * distanceBetweenTiles;
						//Note that the distanceBetweenTiles is 1 for the most part, 1.414 if it's a diaganol

						//If neighbor is in open list (this will not be the first time around)
						//Re-evaluate neighbor F and G; we are now further along the path and the neighbor's costs
						//will have increased because of this
						if (BestTile->NeighborMapTiles[i]->open) {
							//This neighbor's F
							if (newF < BestTile->NeighborMapTiles[i]->fCost) {
								BestTile->NeighborMapTiles[i]->gCost = newG;
								BestTile->NeighborMapTiles[i]->fCost = newF;
								BestTile->NeighborMapTiles[i]->ParentMapTile = BestTile;								
							}
							continue;
						}

						//If the neighbor tile isn't in the Open or Closed list
						//Evaluate tile F and G
						BestTile->NeighborMapTiles[i]->fCost = newF; //Set new F and G
						BestTile->NeighborMapTiles[i]->gCost = newG;
						BestTile->NeighborMapTiles[i]->ParentMapTile = BestTile;
						BestTile->NeighborMapTiles[i]->open = true; //Add this neighbor to the open list
						OpenList.push_back(BestTile->NeighborMapTiles[i]);

					}
				}
			}
		}

		return std::vector<MapCoordinates>(); //No path found, return an empty path	
	}
	catch(...)
	{
		Debugger.print("Error in PathFinding.getPath()");
		return std::vector<MapCoordinates>();
	}
}

float Pathfinder::_getDistanceBetweenPoints(MapCoordinates A, MapCoordinates B)
{
	return abs(A.x - B.x) + abs(A.y - B.y);
}