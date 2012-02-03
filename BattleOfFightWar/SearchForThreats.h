#ifndef _SEARCH_ACTION_SEARCH_FOR_THREATS_
#define _SEARCH_ACTION_SEARCH_FOR_THREATS_

#include "SearchAction.h"
#include "LivingEntityGraphics.h" //For facing constants

class SearchForThreats: public SearchAction
{

	public:

		SearchForThreats(ActionUser* ActionUser);

		void search();
};

#endif