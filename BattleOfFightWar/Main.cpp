#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
//#include <time.h>
//#include <iostream>

#include "RawInputz.h"

#pragma comment(lib, "d3d9.lib")

using namespace std;

//Everything else you need and you made :) -------------------------------

//The whole game (loL?)
Game _Game;

//Controller
Controller _Controller(&_Game);

//Raw input receiver
RawInputz _RawInput(&_Controller);
//------------------------------------------------------------------------

void EndEverything()
{
	Debugger.print("Application closing...");

	_RawInput.releaseRawInputz();
	_Controller.releaseController();

	_Game.releaseGame();

	GlobalDirectXStuff.releaseDirectXStuff();

	Debugger.releaseDebug();
}

/** Windows event handling function; pass control to DirectXStuff::WinProc */
LRESULT winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Recover the pointer to our class, don't forget to type cast it back
	// Note that the pointer was set upon creation of the RawInputz class using SetWindowLong
    RawInputz *winptr = (RawInputz*)GetWindowLong(hWnd, GWL_USERDATA);

    // Check if the pointer is NULL and call the Default WndProc
    if (winptr == NULL) 
	{
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
	else 
	{
        return winptr->myWinProc(hWnd, msg, wParam, lParam);
    }
     
}//end WinProc

/** Helper function for window class registration */
ATOM registerClass(HINSTANCE hInstance)
{
     //Set the new window's properties
     WNDCLASSEX wc;
     wc.cbSize        = sizeof(WNDCLASSEX);
     wc.style         = CS_HREDRAW | CS_VREDRAW;
     wc.lpfnWndProc   = (WNDPROC)winProc;
     wc.cbClsExtra    = 0;
     wc.cbWndExtra    = 0;
     wc.hInstance     = hInstance;
     wc.hIcon         = NULL;
     wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
     wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
     wc.lpszMenuName  = NULL;
     wc.lpszClassName = APPTITLE.c_str();
     wc.hIconSm       = NULL;
     return RegisterClassEx(&wc); 
     
}//end MyRegisterClass

/** Main Windows entry function */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine,
     int nCmdShow)
{
	 Debugger.print("Application starting...");
	 //Window handle
	 HWND window = NULL;

     //register window class
	 registerClass(hInstance);

	 //create window
	 window = CreateWindow(APPTITLE.c_str(), APPTITLE.c_str(),
        WS_OVERLAPPED,
        CW_USEDEFAULT, CW_USEDEFAULT,
        SCREEN_WIDTH, SCREEN_HEIGHT, //Doing SCREEN_WIDTH + 7 AND SCREEN_HEIGHT + 7 causes the map to no longer render... why?
        NULL, NULL, hInstance, NULL
	 );
     
     //was there error in creating window?
     if (window == 0) return 0;
     
     //display the window
     ShowWindow(window, nCmdShow);
     UpdateWindow(window);
     
	 //initialize base directx stuff
	 if (!GlobalDirectXStuff.initDirectXStuff(window, SCREEN_WIDTH, SCREEN_HEIGHT, false)) {
		EndEverything();
		return 0;
	 }

	 //initialize game!
	 if (!_Game.initGame()) {
		EndEverything();
		return 0;
	 }

	 //initialize raw input; needs to be done after game because it relies on it through controller
	 if (!_RawInput.initRawInputz(window)) {
		EndEverything();
		return 0;
	 }

	 MSG message;

	 //main intro loop
	 while ((_Game.isGameOver() == false))
	 {
	     if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
         {
             TranslateMessage(&message);
             DispatchMessage(&message);
         }

		 if ((_Game.isGamePaused() == false))
		 {
			 _Game.runGame();
		 } else {
		     Sleep(10);
		 }
	 }
     
     EndEverything();

     return message.wParam;
     
}//end WinMain