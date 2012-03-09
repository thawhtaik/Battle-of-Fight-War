#ifndef _GAME_WORLD_
#define _GAME_WORLD_

#include "Trooper.h"
#include "Player.h"
#include "Map.h"
#include "Pathfinder.h"

#include "LivingEntitiesList.h"
#include "ProjectileList.h"
#include "AnimatedEffectsList.h"
#include "Cursor.h"

const int NUM_ASSHOLES = 10;

extern Map WorldMap;

extern LivingEntitiesList GlobalLivingEntitiesList;
extern ProjectileList GlobalProjectileList;
extern AnimatedEffectsList GlobalAnimatedEffectsList;
extern Cursor GlobalCursor;

class GameWorld
{

	public:
		GameWorld();

		bool initGameWorld();
		void releaseGameWorld();

		void updateGameWorld();
		void renderGameWorld();

		Player* getPlayer();

	private:

		void _updateAllLivingEntityTilePositions();
		void _updateLivingEntityTilePosition(LivingEntity* LivingEntity, int entityIndex);

		void _clearAllLivingEntityTilePositions();
		void _clearLivingEntityTilePosition(LivingEntity* LivingEntity, int entityIndex);
		void _removeDeadEntities();

		MapCoordinates _Start;
		MapCoordinates _Goal;
		std::vector<MapCoordinates> _Path;
		Pathfinder _Pathfinder;
		Sprite _PathSprite;

		int _playerId;
};

#endif