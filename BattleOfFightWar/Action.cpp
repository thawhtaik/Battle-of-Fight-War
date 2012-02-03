#include "Action.h"

Action::Action()
{
	this->_actionStartTime = timeGetTime();

	this->_ActionUser = NULL;
}