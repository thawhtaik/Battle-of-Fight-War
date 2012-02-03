/** RawInputz.h
    To handle input because the tutorial is gay
*/

//most importantly include directx9 header and library
#ifndef _RAW_INPUTZ_
#define _RAW_INPUTZ_

#include <windows.h>
#include <windowsx.h> //For WM_MOUSEMOVE macros
#include <sstream>

#include "Controller.h"

//Mouse position seems to be different from pixel coordinates
const int X_PIXELS_LOST = (1024/7);
const int Y_PIXELS_LOST = (768/33);

/** Actually takes input from keyboard and mouse, using controller to change game stuff 
*/

class RawInputz
{
    public:

	    RawInputz(Controller* newController); //Ctor

		bool initRawInputz(HWND window); //Initialize everything	

		//WinProc function
		LRESULT myWinProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

		void releaseRawInputz();

	private:

		void _resetKeyPressed();
		void _resetMousePressed();

		//Pointer to controller so you can change shit in the game (its the whole point dummy)
		Controller* _Controller;

		//Raw input from keyboard
		RAWINPUTDEVICE _RawInputDevice[2];

		//Buffer for raw input
		//Determine how big the buffer should be (mouse size is 40 and the keyboard 32)
		UINT _bufferSize;
		//For checking buffer size once input is received
		UINT _checkBufferSize;

		// Create a buffer of the correct size for collecting raw input stream
		BYTE* _buffer;
		//For casting raw input
		RAWINPUT* _raw;
		//For getting the keyCode from raw
		USHORT _keyCode;

		//Check if key is released
		bool _keyUp;
		//Check if key is held down
		bool _keyDown;

		//Similarly for mouse clicks
		bool _mouseUp;
		bool _mouseDown;

		//Raw mouse x and y values
		long _lastMouseX;
		long _lastMouseY;

		long _currentMouseX;
		long _currentMouseY;

		//Prepping the raw input for use in WM_INPUT
		LRESULT _prepareRawInput(HWND window, LPARAM lParam);

		//Generic pause/unpause functions
		LRESULT handleGenericMessages(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif