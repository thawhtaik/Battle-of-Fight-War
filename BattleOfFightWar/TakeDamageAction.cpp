#include "TakeDamageAction.h"

TakeDamageAction::TakeDamageAction(ActionUser* ActionUser)
{
	this->_ActionUser = ActionUser;
	this->_ActionUser->setAnimationEffect(ANIMATION_EFFECT_BLEEDING);

	this->_actionWindUpTime = 80;
	this->_damageFinished = false;
	this->_actionStartTime = 0;
	this->_timeTick = 0;
}

void TakeDamageAction::releaseAction()
{
	this->_ActionUser = NULL;
}


bool TakeDamageAction::isActionFinished()
{
	return this->_damageFinished;
}

void TakeDamageAction::doAction()
{
	this->_timeTick++;

	if (this->_timeTick - this->_actionStartTime >= this->_actionWindUpTime) {
		this->_damageFinished = true;
		this->_ActionUser->setAnimationEffect(ANIMATION_EFFECT_STOP_BLEEDING);
	}
}