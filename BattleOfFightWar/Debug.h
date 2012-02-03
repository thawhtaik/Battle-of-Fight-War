#ifndef _DEBUGZOR_
#define _DEBUGZOR_

#include <fstream>

#include <d3dx9.h>

class Debug
{
	public:

		Debug();
		void releaseDebug();

		void print(char c[]);
		void end(int nr);

		/** Overloading ofstream operators */
		std::ofstream& operator<<(char c[]);
		std::ofstream& operator<<(int i);
		std::ofstream& operator<<(float f);
		std::ofstream& operator<<(bool b);
		std::ofstream& operator<<(D3DXVECTOR3 v);
};

static Debug Debugger;

#endif