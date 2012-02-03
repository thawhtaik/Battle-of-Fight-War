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