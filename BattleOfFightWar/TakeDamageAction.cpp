#include "TakeDamageAction.h"

TakeDamageAction::TakeDamageAction(ActionUser* ActionUser, int damage, short damageType, short damageDirection)
{
	this->_ActionUser = ActionUser;

	this->_actionWindUpTime = 80;
	this->_damageTargetFinished = false;
	this->_actionStartTime = 0;
	this->_timeTick = 0;

	this->_damage = damage;
	this->_damageType = damageType;
}

void TakeDamageAction::releaseAction()
{
	this->_ActionUser = NULL;
}


bool TakeDamageAction::isActionFinished()
{
	return this->_damageTargetFinished;
}

void TakeDamageAction::doAction()
{
	this->_damageTargetFinished = true;
}