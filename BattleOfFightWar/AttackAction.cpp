#include "AttackAction.h"

AttackAction::AttackAction(ActionUser* ActionUser)
{
	this->_ActionUser = ActionUser;

	this->_actionWindUpTime = this->_ActionUser->getCurrentWeapon()->getAttackWindUpTime();
	this->_attackFinished = false;
	this->_actionStartTime = 0;
	this->_timeTick = 0;
}

void AttackAction::releaseAction()
{
	this->_ActionUser = NULL;
}


bool AttackAction::isActionFinished()
{
	return this->_attackFinished;
}

void AttackAction::doAction()
{
	this->_timeTick++;

	if (this->_timeTick - this->_actionStartTime >= this->_actionWindUpTime) {

		Weapon* UserWeapon = this->_ActionUser->getCurrentWeapon();
		UserWeapon->attack(this->_ActionUser);
		this->_attackFinished = true;

		this->_ActionUser->setAnimationEffect(ANIMATION_EFFECT_MUZZLE_FLASH);
	}
}