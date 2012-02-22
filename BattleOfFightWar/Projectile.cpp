#include "Projectile.h"

Projectile::Projectile()
{
	this->_distanceTravelled = 0;
	this->_amountOfCoverPassed = 0;

	this->_ProjectileTexture = NULL;

	this->_velocityX = 0;
	this->_velocityY = 0;

	this->_functional = true;
}

void Projectile::update()
{
	this->Position.x += this->_velocityX;
	this->Position.y += this->_velocityY;

	this->_ProjectileSprite.x = this->Position.x;
	this->_ProjectileSprite.y = this->Position.y;



	MapTile* Tile = WorldMap.getTileAtPosition(Position.x, Position.y);
	if (Tile == NULL) {
		this->_functional = false;
		return;
	}

	if (this->_hasCollisionOnTile(Tile)) {
		return;	
	}

	for (int i = 0; i < 8; i++) {

		MapTile* NeighborTile = Tile->NeighborMapTiles[i];

		if (NeighborTile != NULL && NeighborTile->walkable) {
			if (this->_hasCollisionOnTile(NeighborTile)) {
				return;	
			}
		}
	}

	//MapCoordinates TileCoordinates = Tile->TileCoordinates;

	//MapTile* TilesToCheckForCollision[9];
	//int surroundingTilesIndex = 0;

	//int bottomRightX = this->Position.x;
	//int bottomRightY = this->Position.y;

	//for (int i = 0; i < 8; i++) {
	//	MapTile* NeighborTile = Tile->NeighborMapTiles[i];
	//	if (NeighborTile != NULL && NeighborTile->walkable) {
	//		TilesToCheckForCollision[surroundingTilesIndex] = NeighborTile;
	//		surroundingTilesIndex++;
	//	}
	//}

	////Don't forget our starting tile too!
	//TilesToCheckForCollision[surroundingTilesIndex] = Tile;
	//surroundingTilesIndex++;

	//int bottomRightX = this->Position.x;
	//int bottomRightY = this->Position.y;

	//for (int i = 0; i < surroundingTilesIndex; i++) {

	//	set<int> tileLivingEntityIndices = TilesToCheckForCollision[i]->currentLivingEntityIndices;

	//	set<int>::iterator setIterator;

	//	for (setIterator = tileLivingEntityIndices.begin(); setIterator != tileLivingEntityIndices.end(); setIterator++) {

	//		int livingEntityIndex = *setIterator;

	//		WorldObject* LivingEntity = GlobalLivingEntitiesList.getAtIndex(livingEntityIndex);

	//		if (!(Position.x > LivingEntity->positionX + LivingEntity->sizeX || bottomRightX < LivingEntity->positionX ||		
	//			Position.y > LivingEntity->positionY + LivingEntity->sizeY || bottomRightY < LivingEntity->positionY)
	//		) {
	//			this->_functional = false;
	//		}
	//	}
	//}
}


void Projectile::releaseProjectile()
{
	this->_ProjectileTexture = NULL;
}


void Projectile::_determineMovement(short newVelocity)
{
	int distanceX = this->_TargetPosition.x - this->Position.x;
	int distanceY = this->_TargetPosition.y - this->Position.y;

	float angle = 0.0;
	if (distanceX == 0) {
		if (distanceY >= 0) {
			angle = PI/2;
		} else {
			angle = -PI/2;
		}
	} else {
		angle = atan(((float)distanceY/(float)distanceX));
	
		if (distanceX <= 0 && distanceY <= 0) {
			angle += PI;
		} else if (distanceX <= 0) {
			angle -= PI;
		}
	}

	this->_velocityY = newVelocity * sin(angle);
	this->_velocityX = newVelocity * cos(angle);

	this->_ProjectileSprite.rotation = angle;

	this->_ProjectileSprite.x = this->Position.x;
	this->_ProjectileSprite.y = this->Position.y;
}


bool Projectile::_hasCollisionOnTile(MapTile* MapTile)
{
	set<int> tileLivingEntityIndices = MapTile->currentLivingEntityIndices;

	set<int>::iterator setIterator;

	for (setIterator = tileLivingEntityIndices.begin(); setIterator != tileLivingEntityIndices.end(); setIterator++) {

		int livingEntityIndex = *setIterator;

		WorldObject* LivingEntity = GlobalLivingEntitiesList.getAtIndex(livingEntityIndex);

		//Really it should be seeing if topLeft x, topLeft y, bottomRight x, or bottomRight y are outside the LivingEntity rectangle, but since
		//our bullet is very small we'll just treat it as a point
		if (LivingEntity->isPositionInObjectHitbox(this->Position)) {
			
			MapCoordinates BloodPosition = MapCoordinates();
			switch (this->_facing) {

				case ENTITY_FACING_EAST:
				case ENTITY_FACING_WEST:
					BloodPosition.x = this->Position.x - SPRITE_SIZE_MEDIUM/2;
					BloodPosition.y = this->Position.y  - SPRITE_SIZE_MEDIUM/2;
					break;
				default:
					BloodPosition.x = this->Position.x;
					BloodPosition.y = this->Position.y;
					break;
			}

			AnimatedEffectCreator::createBleedingEffect(BloodPosition);

			LivingEntity->damage();
			this->_functional = false;

			return true;
		}
	}

	return false;
}


bool Projectile::isFunctional()
{
	return this->_functional;
}