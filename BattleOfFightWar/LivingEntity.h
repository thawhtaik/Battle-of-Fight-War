#ifndef _LIVING_ENTITY_
#define _LIVING_ENTITY_

#include <stdlib.h>

#include "WorldObject.h"

#include "ActionUser.h"
#include "WeaponSelector.h"

//Actions
#include "Action.h"
#include "AttackAction.h"
#include "TakeDamageAction.h"

#include "LifeStatus.h"
#include "Brain.h"

#include "MovementCollisionChecker.h"

#include "LivingEntityGraphics.h"

const int ENTITY_MOVEMENT_IDLE = 0;
const int ENTITY_MOVEMENT_SOUTH = 1;
const int ENTITY_MOVEMENT_NORTH = 2;
const int ENTITY_MOVEMENT_EAST = 3;
const int ENTITY_MOVEMENT_WEST = 4;

const int ENTITY_MOVEMENT_SOUTHEAST = 5;
const int ENTITY_MOVEMENT_SOUTHWEST = 6;
const int ENTITY_MOVEMENT_NORTHEAST = 7;
const int ENTITY_MOVEMENT_NORTHWEST = 8;


class LivingEntity:public ActionUser
{

	public:
		LivingEntity();

		virtual void initLivingEntityGraphics() = 0;
		virtual void releaseWorldObject() = 0;

		void update();
		void render();

		void setCurrentMovementDirection(int newMovementDirection);
		void moveEntity(int addX, int addY);
		void updateLifeStatus();

		void attack();
		void setCurrentWeapon(short newWeaponType);

		//ActionUser methods
		void setAnimationEffect(int newAnimationEffect);		
		void setCurrentAnimation(int newAnimation);
		int getPositionX();
		int getPositionY();
		int getFacing();
		int getIndex();

		LifeStatus* getLifeStatus();
		Weapon* getCurrentWeapon();

		//Target methods
		void damage();

	protected:

		Weapon* _CurrentWeapon;

		LifeStatus _LifeStatus;
		LivingEntityGraphics* _EntityGraphics;

		void _moveBasedOnCurrentMovementDirection();
		void _updateCurrentGoal();
		void _determineCurrentMovementDirection();
		void _updateEventActions();

		void _setCurrentFacing(int newFacing);
		void _moveIfPositionNotOccupied(int addX, int addy);

		short _currentFacing;
		short _currentMovementDirection;
		
		//
		//Actions
		//
		std::vector<Action*> _CurrentActions;

		//
		//LivingEntity AI stuff
		//
		Brain _Brain;

		int _currentPathIndex;
		std::vector<MapCoordinates> _CurrentPath;

		Goal* _CurrentGoal;
};


#endif