#include "LivingEntity.h"

LivingEntity::LivingEntity()
{
	this->_Brain = Brain::Brain();

	this->_CurrentPath.clear();
	this->_currentPathIndex = this->_currentMovementDirection = 0; 

	this->_CurrentGoal = NULL;
	this->_EntityGraphics = NULL;
	this->_CurrentWeapon = NULL;

	this->_currentFacing = ENTITY_FACING_SOUTH;

	this->objectIndex = this->sizeX = this->sizeY = this->hitboxSizeX = this->hitboxSizeY = 0;

	this->_updateFunctionPointer = &LivingEntity::_updateNormal;
	this->_moveFunctionPointer = &LivingEntity::_noMovement;


	this->removeFromPlay = false;
}


void LivingEntity::render()
{
	this->_EntityGraphics->positionX = this->positionX;
	this->_EntityGraphics->positionY = this->positionY;

	this->_EntityGraphics->animate();

	this->_EntityGraphics->render();
}

void LivingEntity::update()
{
	(this->*_updateFunctionPointer)();
}

void LivingEntity::_updateNormal()
{
	this->_updateCurrentGoal();

	this->_determineCurrentMovementDirection();

	this->_moveBasedOnCurrentMovementDirection();

	this->_updateEventActions();
}


void LivingEntity::_updateCurrentGoal()
{
	SearchForThreats SearchThreatsAction(this);
	SearchThreatsAction.search();
	SearchThreatsAction.releaseSearchAction();

	if (this->_CurrentGoal != NULL) {

		if (this->_CurrentGoal->isActionInRange()) {
			this->_CurrentGoal->doAction();

			/* Add in this piece if you have an action that needs to re-evaluate a goal
			else {
				this->_CurrentGoal->findTarget(LifeStatus);
				this->_CurrentPath = this->_getPathFromGoal(LifeStatus);
			}*/

		}

		if (this->_CurrentGoal->isActionFinished()) {
			this->_CurrentGoal->releaseGoal();
			delete this->_CurrentGoal;
			this->_CurrentGoal = NULL;
		}

	} else {
		this->_CurrentGoal = this->_Brain.determineGoal(this);
		this->_CurrentGoal->findTarget();
		MapCoordinates CurrentPosition(this->positionX, this->positionY);
		this->_CurrentPath = this->_Brain.getPathFromGoal(CurrentPosition, this->_CurrentGoal);
	}

}


void LivingEntity::_determineCurrentMovementDirection()
{
	int newMovementDirection = MOVEMENT_DIRECTION_IDLE;

	if (!this->_CurrentPath.empty()) {

		MapCoordinates CurrentPosition(this->positionX, this->positionY);

		newMovementDirection = this->_Brain.getMovementDirectionFromCurrentPosition(
			CurrentPosition, &this->_CurrentPath, this->_currentPathIndex
		);

		if (newMovementDirection == MOVEMENT_DIRECTION_IDLE) {
			//No movement? Let's try the next tile on the path
			this->_currentPathIndex++;

			if (this->_currentPathIndex > this->_CurrentPath.size() - 1) {
				//Oh wait, we're done here, no more path
				this->_currentPathIndex = 0;
				this->_CurrentPath.clear();
			}
		}
	}	

	this->setCurrentMovementDirection(newMovementDirection);
}


void LivingEntity::_moveBasedOnCurrentMovementDirection()
{
	(this->*_moveFunctionPointer)();
}


void LivingEntity::setCurrentMovementDirection(int newMovementDirection)
{
	if (this->_currentMovementDirection == newMovementDirection) {
		return;
	}

	this->_currentMovementDirection = newMovementDirection;

	this->_EntityGraphics->setCurrentAnimationState(ENTITY_ANIMATION_RUNNING);

	switch (this->_currentMovementDirection) {
		case ENTITY_MOVEMENT_NORTH:
			this->_moveFunctionPointer = &LivingEntity::_moveNorth;
			this->_setCurrentFacing(ENTITY_FACING_NORTH);
			break;
		case ENTITY_MOVEMENT_SOUTH:
			this->_moveFunctionPointer = &LivingEntity::_moveSouth;
			this->_setCurrentFacing(ENTITY_FACING_SOUTH);
			break;
		case ENTITY_MOVEMENT_EAST:
			this->_moveFunctionPointer = &LivingEntity::_moveEast;
			this->_setCurrentFacing(ENTITY_FACING_EAST);
			break;
		case ENTITY_MOVEMENT_WEST:
			this->_moveFunctionPointer = &LivingEntity::_moveWest;
			this->_setCurrentFacing(ENTITY_FACING_WEST);
			break;
		case ENTITY_MOVEMENT_SOUTHEAST:
			this->_moveFunctionPointer = &LivingEntity::_moveSoutheast;
			this->_setCurrentFacing(ENTITY_FACING_SOUTHEAST);
			break;
		case ENTITY_MOVEMENT_SOUTHWEST:
			this->_moveFunctionPointer = &LivingEntity::_moveSouthwest;
			this->_setCurrentFacing(ENTITY_FACING_SOUTHWEST);
			break;
		case ENTITY_MOVEMENT_NORTHEAST:
			this->_moveFunctionPointer = &LivingEntity::_moveNortheast;
			this->_setCurrentFacing(ENTITY_FACING_NORTHEAST);
			break;
		case ENTITY_MOVEMENT_NORTHWEST:
			this->_moveFunctionPointer = &LivingEntity::_moveNorthwest;
			this->_setCurrentFacing(ENTITY_FACING_NORTHWEST);
			break;
		case ENTITY_MOVEMENT_IDLE:
			this->_EntityGraphics->setCurrentAnimationState(ENTITY_ANIMATION_IDLE);
			this->_moveFunctionPointer = &LivingEntity::_noMovement;
			break;
	}
}


void LivingEntity::_moveSouth()
{
	this->moveEntity(0, +1);
}


void LivingEntity::_moveNorth()
{
	this->moveEntity(0, -1);
}


void LivingEntity::_moveEast()
{
	this->moveEntity(+1, 0);
}


void LivingEntity::_moveWest()
{
	this->moveEntity(-1, 0);
}


void LivingEntity::_moveSoutheast()
{
	this->moveEntity(+1, +1);
}


void LivingEntity::_moveSouthwest()
{
	this->moveEntity(-1, +1);
}


void LivingEntity::_moveNortheast()
{
	this->moveEntity(+1, -1);
}


void LivingEntity::_moveNorthwest()
{
	this->moveEntity(-1, -1);
}


void LivingEntity::_noMovement()
{
}


void LivingEntity::moveEntity(int addX, int addY)
{
	int xDisplacement = abs(addX);
	int yDisplacement = abs(addY);

	this->_moveIfPositionNotOccupied(addX, addY);
}

void LivingEntity::_moveIfPositionNotOccupied(int addX, int addY) 
{
	int futurePositionX = this->positionX + addX;
	int futurePositionY = this->positionY + addY;
	MapCoordinates FuturePosition(futurePositionX, futurePositionY);

	if (!MovementCollisionChecker::isLivingEntityInPosition(FuturePosition, this->sizeX, this->sizeY, this->objectIndex)) {
		this->positionX = futurePositionX;
		this->positionY = futurePositionY;
	}

}

void LivingEntity::_setCurrentFacing(int newFacing)
{
	if (this->_currentFacing == newFacing) {
		return;
	}

	this->_currentFacing = newFacing;

	this->_EntityGraphics->setCurrentSpriteFacing(this->_currentFacing);
}


void LivingEntity::_updateEventActions()
{
	for (int i = 0; i < this->_CurrentActions.size(); i++) {
		this->_CurrentActions.at(i)->doAction();

		if (this->_CurrentActions.at(i)->isActionFinished()) {
			this->_CurrentActions.at(i)->releaseAction();
			delete this->_CurrentActions.at(i);
			this->_CurrentActions.erase(this->_CurrentActions.begin() + i);
		}
	}
}


void LivingEntity::setCurrentWeapon(short newWeaponType)
{
	this->_CurrentWeapon = WeaponSelector::getWeaponBasedOnType(newWeaponType);
	this->_EntityGraphics->setWeaponType(newWeaponType);
}


//
// Death
//

void LivingEntity::_updateDeath()
{
	this->_updateEventActions();
}


//
//ActionUser "interface" methods
//

void LivingEntity::setPosition(MapCoordinates NewPosition)
{
	this->positionX = NewPosition.x;
	this->positionY = NewPosition.y;
}


int LivingEntity::getPositionX()
{
	return this->positionX;
}

int LivingEntity::getPositionY()
{
	return this->positionY;
}

int LivingEntity::getFacing()
{
	return this->_currentFacing;
}

LifeStatus* LivingEntity::getLifeStatus()
{
	return &this->_LifeStatus;
}

int LivingEntity::getIndex()
{
	return this->objectIndex;
}

Weapon* LivingEntity::getCurrentWeapon()
{
	return this->_CurrentWeapon;
}


void LivingEntity::removeEntityFromPlay()
{
	this->removeFromPlay = true;
}


//
// Still on ActionUser methods; animation methods
//

void LivingEntity::setCurrentAnimation(int newAnimation)
{
	this->_EntityGraphics->setCurrentAnimationState(newAnimation);
}


void LivingEntity::setAnimationEffect(int newAnimationEffect)
{
	this->_EntityGraphics->setAnimationEffect(newAnimationEffect);
}


//
// Attacker methods
//

void LivingEntity::attack()
{
	MapCoordinates BsMapCoordinates = MapCoordinates(0, 0);
	//Start attack action
	Action* Attack = new AttackAction(this, BsMapCoordinates);
	this->_CurrentActions.push_back(Attack);
}


//
// Target methods (Target->WorldObject->LivingEntity)
//

void LivingEntity::damage(int damage, short damageType, short damageDirection)
{
	/*Action* TakeDamage = new TakeDamageAction(this, damage, damageType);
	this->_CurrentActions.push_back(TakeDamage);*/

	if (this->_updateFunctionPointer == &LivingEntity::_updateDeath) {
		return;
	}

	this->_LifeStatus.damage(damage);

	if (this->_LifeStatus.hitPoints <= 0) {
		
		//Set living entity to "dead mode"
		this->_EntityGraphics->setCurrentAnimationState(ENTITY_ANIMATION_DYING);
		this->_updateFunctionPointer = &LivingEntity::_updateDeath;

		//Clear all actions since this guy is DEAD
		for (int i = 0; i < this->_CurrentActions.size(); i++) {
			this->_CurrentActions.at(i)->releaseAction();
		}
		this->_CurrentActions.clear();
		
		DieAction* Die = new DieAction(this, damageDirection);
		this->_CurrentActions.push_back(Die);
	}
}


