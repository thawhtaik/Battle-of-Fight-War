#ifndef _TARGET_
#define _TARGET_

class Target
{

	public:
		virtual void damage(int damage, short damageType, short damageDirection) = 0;
};


#endif