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

	this->objectIndex = this->sizeX = this->sizeY = 0;
}

void LivingEntity::updateLifeStatus()
{
	this->_LifeStatus.update();
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
	this->updateLifeStatus();

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


void LivingEntity::setCurrentMovementDirection(int newMovementDirection)
{
	this->_currentMovementDirection = newMovementDirection;
}


void LivingEntity::_moveBasedOnCurrentMovementDirection()
{
	switch (this->_currentMovementDirection) {
		case ENTITY_MOVEMENT_NORTH:
			this->moveEntity(0, -1);
			break;
		case ENTITY_MOVEMENT_SOUTH:
			this->moveEntity(0, +1);
			break;
		case ENTITY_MOVEMENT_EAST:
			this->moveEntity(+1, 0);
			break;
		case ENTITY_MOVEMENT_WEST:
			this->moveEntity(-1, 0);
			break;
		case ENTITY_MOVEMENT_SOUTHEAST:
			this->moveEntity(+1, +1);
			break;
		case ENTITY_MOVEMENT_SOUTHWEST:
			this->moveEntity(-1, +1);
			break;
		case ENTITY_MOVEMENT_NORTHEAST:
			this->moveEntity(+1, -1);
			break;
		case ENTITY_MOVEMENT_NORTHWEST:
			this->moveEntity(-1, -1);
			break;

		case ENTITY_MOVEMENT_IDLE:
			this->_EntityGraphics->setCurrentAnimationState(ENTITY_ANIMATION_IDLE);
			break;
	}
}


void LivingEntity::moveEntity(int addX, int addY)
{
	int xDisplacement = abs(addX);
	int yDisplacement = abs(addY);

	if (xDisplacement >= yDisplacement) {
		if (addX > 0) {
			this->_setCurrentFacing(ENTITY_FACING_EAST);
		} else {
			this->_setCurrentFacing(ENTITY_FACING_WEST);
		}
	} else {
		if (addY > 0) {
			this->_setCurrentFacing(ENTITY_FACING_SOUTH);
		} else {
			this->_setCurrentFacing(ENTITY_FACING_NORTH);
		}
	}

	this->_EntityGraphics->setCurrentAnimationState(ENTITY_ANIMATION_RUNNING);

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

	switch (newFacing) {

		case ENTITY_FACING_NORTH:
			this->_EntityGraphics->setCurrentSpriteFacing(ENTITY_FACING_NORTH);
			break;
		case ENTITY_FACING_SOUTH:
			this->_EntityGraphics->setCurrentSpriteFacing(ENTITY_FACING_SOUTH);
			break;
		case ENTITY_FACING_EAST:
			this->_EntityGraphics->setCurrentSpriteFacing(ENTITY_FACING_EAST);
			break;
		case ENTITY_FACING_WEST:
			this->_EntityGraphics->setCurrentSpriteFacing(ENTITY_FACING_WEST);
			break;
	}
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
//ActionUser "interface" methods
//

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
	//Start attack action
	Action* Attack = new AttackAction(this);
	this->_CurrentActions.push_back(Attack);
}


//
// Target methods (Target->WorldObject->LivingEntity)
//

void LivingEntity::damage()
{
	Action* TakeDamage = new TakeDamageAction(this);
	this->_CurrentActions.push_back(TakeDamage);
}


