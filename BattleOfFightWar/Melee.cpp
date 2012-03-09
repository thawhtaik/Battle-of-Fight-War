#include "Melee.h"

Melee::Melee(int newAttackPower, int newRange, int newCoolDown, int newWindUpTime)
{
	this->_attackPower = newAttackPower;
	this->_range = newRange;
	this->_coolDown = newCoolDown;
	this->_attackWindUpTime = newWindUpTime;
}

void Melee::attack(WorldObject* Attacker, MapCoordinates TargetPosition)
{
	int attackerPositionX = Attacker->getPositionX();
	int attackerPositionY = Attacker->getPositionY();

	MapTile* Tile = WorldMap.getTileAtPosition(attackerPositionX, attackerPositionY);
	MapCoordinates TileCoordinates = Tile->TileCoordinates;

	////Check which tiles based on attacker facing
	//switch (Attacker->getFacing()) {

	//}

	
	MapTile* TilesToCheckForTargets[9];
	int surroundingTilesIndex = 0;

	for (int i = 0; i < 8; i++) {
		MapTile* NeighborTile = Tile->NeighborMapTiles[i];
		if (NeighborTile != NULL && NeighborTile->walkable) {
			TilesToCheckForTargets[surroundingTilesIndex] = NeighborTile;
			surroundingTilesIndex++;
		}
	}
	//Don't forget our starting tile too!
	TilesToCheckForTargets[surroundingTilesIndex] = Tile;
	surroundingTilesIndex++;

	for (int i = 0; i < surroundingTilesIndex; i++) {

		set<int> tileLivingEntityIndices = TilesToCheckForTargets[i]->currentLivingEntityIndices;
		int attackerIndex = Attacker->getIndex();

		set<int>::iterator setIterator;
		for (setIterator = tileLivingEntityIndices.begin(); setIterator != tileLivingEntityIndices.end(); setIterator++) {

			int livingEntityIndex = *setIterator;

			if (livingEntityIndex == attackerIndex) {
				continue;
			}

			//Damage target if it's in range
			WorldObject* TargetLivingEntity = GlobalLivingEntitiesList.getAtIndex(livingEntityIndex);
			if (this->_isTargetInDamageRange(Attacker, TargetLivingEntity)) {
				TargetLivingEntity->damage(this->_attackPower, this->_damageType, 0); //Handle damage direction at some point
			}
		}
	}
}