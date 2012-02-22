#ifndef _ATTACKER_
#define _ATTACKER_

class Attacker
{

	public:
		virtual void attack() = 0;

		virtual void setCurrentAnimation(int newAnimation) = 0;
		virtual void setAnimationEffect(int newAnimation) = 0;
};

#endif