#include "Player.h"

Player::Player()
{
}

Player::Player(LivingEntityGraphics* NewLivingEntityGraphics)
{
	this->_EntityGraphics = NULL;
	this->_EntityGraphics = NewLivingEntityGraphics;
}

void Player::update()
{
	this->updateLifeStatus();
	this->_moveBasedOnCurrentMovementDirection();

	this->_updateEventActions();
}


void Player::lookAtPosition(MapCoordinates Position)
{
	int playerCenterX = this->positionX + TROOPER_BODY_SPRITE_SIZE_HALF;
	int playerCenterY = this->positionY + TROOPER_BODY_SPRITE_SIZE_HALF;

	int differenceX = Position.x - playerCenterX;
	int differenceY = Position.y - playerCenterY;

	float angle = atan(((float)differenceY/(float)differenceX));

	//std::string stringAngle("Player angle: %f", angle);
	char buf[2048];
	sprintf(buf,"Player angle: %f \n", angle);

	OutputDebugString(buf);

	//So this crap is all flipped because of the ass-backwards coordinate system
	//i.e. instead of ASTC its CTSA
	//THIS IS HORRIBLE CHANGE IT ASAP
	if (angle >= 0) {
		if (differenceX >= 0) { //Quadrant 1
			if (angle >= PI/8 && angle <= (3*PI)/8) {
				this->_setCurrentFacing(ENTITY_FACING_SOUTHEAST);
			} else if (angle >= PI/8) {
				this->_setCurrentFacing(ENTITY_FACING_SOUTH);
			} else {
				this->_setCurrentFacing(ENTITY_FACING_EAST);
			}
		} else { //Quadrant 3
			if (angle >= PI/8 && angle <= (3*PI)/8) {
				this->_setCurrentFacing(ENTITY_FACING_NORTHWEST);
			} else if (angle >= PI/8) {
				this->_setCurrentFacing(ENTITY_FACING_NORTH);
			} else {
				this->_setCurrentFacing(ENTITY_FACING_WEST);
			}
		}
	} else {
		if (differenceX >= 0) { //Quadrant 4
			if (angle <= -PI/6 && angle >= -(2*PI)/6) {
				this->_setCurrentFacing(ENTITY_FACING_NORTHEAST);
			} else if (angle <= -PI/6) {
				this->_setCurrentFacing(ENTITY_FACING_NORTH);
			} else {
				this->_setCurrentFacing(ENTITY_FACING_EAST);
			}
		} else {  //Quadrant 3
			if (angle <= -PI/6 && angle >= -(2*PI)/6) {
				this->_setCurrentFacing(ENTITY_FACING_SOUTHWEST);
			} else if (angle <= -PI/6) {
				this->_setCurrentFacing(ENTITY_FACING_SOUTH);
			} else {
				this->_setCurrentFacing(ENTITY_FACING_WEST);
			}
		}
	}
}


void Player::_moveBasedOnCurrentMovementDirection()
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


//
// Overridden Attacker methods
//

void Player::attack()
{
	Action* Attack = new AttackAction(this, GlobalCursor.Position);
	this->_CurrentActions.push_back(Attack);
}