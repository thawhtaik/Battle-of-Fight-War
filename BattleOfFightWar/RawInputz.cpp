#include "RawInputz.h"

RawInputz::RawInputz(Controller *newController)
{
	this->_Controller = newController;

	//For _raw input (40 is the biggest message you can get)
	this->_bufferSize = 40;

	this->_buffer = new BYTE[_bufferSize];

	this->_resetKeyPressed();
	this->_resetMousePressed();

	this->_lastMouseX = 0;
	this->_lastMouseY = 0;

}

bool RawInputz::initRawInputz(HWND window)
{
	//Adds a pointer to your current class to the WndClassEx structure used by this window
	SetWindowLong(window, GWL_USERDATA, (LONG)this);

	/** Register to receive _raw input from keyboard --------------------------------------------------- */
	/**     
	The usUsagePage is a value for the type of device. Normally we will use 1 here as that stands for "generic 
	desktop controls" and covers all the usual input devices (see the tables below).
	The  usUsage value specifies the device within the "generic desktop controls" group. 2 is mouse, 4 is joystick,
	6 is keyboard (for more see the tables below)
	dwFlags allows various flags to be specified. One useful one is RIDEV_NOLEGACY. If you specify this for the 
	keyboard your program will no longer receive any messages like WM_KEYDOWN (see WndProc notes). If you 
	specify it for the mouse you will no longer get messages like WM_LBUTTONDOWN. This falg can be useful when 
	writing a game running full screen however if you are testing in a window I would suggest not to use them 
	otherwise all menus etc. will not work. Another potentially useful flag is RIDEV_DEVNOTIFY that provides 
	notifications to your window (via WM_INPUT_DEVICE_CHANGE messages) when a device is hot plugged / removed.
	hwndTarget can be used to restrict messages to a particular window. If this is NULL then the current window 
	focus is used.
	*/

	//Might be useful to add RIDEV_DEVNOTIFY messages though

	// Keyboard = 6
	_RawInputDevice[0].usUsagePage = 1;
	_RawInputDevice[0].usUsage = 6;
	_RawInputDevice[0].dwFlags = 0;
	_RawInputDevice[0].hwndTarget=NULL;

	// Mouse
	_RawInputDevice[1].usUsagePage = 1;
	_RawInputDevice[1].usUsage = 2;
	_RawInputDevice[1].dwFlags = 0;
	_RawInputDevice[1].hwndTarget=NULL;

	/** Actual registering of the devices. You must supply an array of devices, the number of devices and the size of the structure. If this returns false an error has occurred. 
	* You need to register your devices after the window has been created but before the first update. So either do it straight after calling CreateWindow in your WinMain or trap the WM_CREATE message in your window procedure and do it there.
	*/
	if (RegisterRawInputDevices(_RawInputDevice,2,sizeof(RAWINPUTDEVICE))==FALSE)
	{
		MessageBox(window, TEXT("Error registering _raw input"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;	
}

/** My winproc function; Default winproc passes control to this */
LRESULT RawInputz::myWinProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{  
	switch (msg) {

	    case WM_INPUT: { 
			//Reading device input
			this->_prepareRawInput(window, lParam);

			if (this->_keyUp == false && this->_raw->header.dwType != RIM_TYPEMOUSE) { //key is held down, no mouse
				//Do stuff with the _keyCode whether it's paused or unpaused
				switch (_keyCode) {
					case VK_PAUSE: //Pause/unpause the game
						if ((this->_Controller->isGamePaused() == false))
						    this->_Controller->setGamePaused(true);
						else
							this->_Controller->setGamePaused(false);
					    break;
					case VK_ESCAPE: //Quit the game
						//MessageBox(window, TEXT("Filler message that immediately gets OK'd with Esc"), TEXT("Nothing"), MB_OK);
                        PostMessage(window, WM_DESTROY, 0, 0); //Note that this gets sent to our "handle generic messages" method
					    break;
					default:
						break;
				}

				//MOST CONTROLS WILL GO HERE
				//Now do stuff with the pressed down key only when it's not paused
				if (this->_Controller->isGamePaused() == false) {
				    switch (this->_keyCode) {
						case VK_CONTROL: //Random message
							MessageBox(window, TEXT("This is what happens when you press CTRL!"), TEXT("BREAKPOINT"), MB_OK);
							break;
						case 'S':
							this->_Controller->movePlayer(TROOPER_MOVEMENT_SOUTH);
							break;
						case 'W':
							this->_Controller->movePlayer(TROOPER_MOVEMENT_NORTH);
							break;
						case 'A':
							this->_Controller->movePlayer(TROOPER_MOVEMENT_WEST);
							break;
						case 'D':
							this->_Controller->movePlayer(TROOPER_MOVEMENT_EAST);
							break;
						case 'F':
							this->_Controller->playerAttack();
							break;
						default:
							break;
			        }//end unpause _keyCode switch

				}//end unpause if
			} else if (this->_keyUp == true ) {
				
				this->_Controller->movePlayer(TROOPER_MOVEMENT_IDLE);

				//Reset current states to ready for next WM_INPUT	
				this->_resetKeyPressed();
		    }
			
			if (this->_mouseDown == true) { //Mouse counts as being held down until we get an up-flag... which will be almost always
				/*this->_Controller->setPath(this->_currentMouseX, this->_currentMouseY);*/
				/*MessageBox(
					window, 
					TEXT("Mouse click received!"), TEXT("BREAKPOINT"), MB_OK
				);
				this->_resetMousePressed();*/
			}

            break; 

		}//break out of WM_INPUT

		//Mouse movement!
		case WM_MOUSEMOVE:
			//this->_Controller->updateCursorCoordinates(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			this->_currentMouseX = GET_X_LPARAM(lParam) + (GET_X_LPARAM(lParam)/X_PIXELS_LOST);
			this->_currentMouseY = GET_Y_LPARAM(lParam) + (GET_Y_LPARAM(lParam)/Y_PIXELS_LOST);
			this->_Controller->updateMapTileCoordinates(this->_currentMouseX, this->_currentMouseY);

			this->_Controller->updateCursorPosition(this->_lastMouseX, this->_lastMouseY);
			break;

		default: //Handle anything not specific to game (program shit)
			this->handleGenericMessages(window, msg, wParam, lParam);
			break;

    }//end switch

	//We do not want to handle this message so pass back to Windows to handle it in a default way
    return DefWindowProc(window, msg, wParam, lParam);
	
}//end WinProc

LRESULT RawInputz::handleGenericMessages(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_SIZE: //Pause game if it is minimized
		    if (wParam == SIZE_MINIMIZED)
				_Controller->setGamePaused(true);
			else
				_Controller->setGamePaused(false); //resume if not minimized
			break;
		case WM_ENTERSIZEMOVE: //Pause game if it is being resized?
			_Controller->setGamePaused(true);
			break;
		case WM_ENTERMENULOOP: //Pause game if menu used?
			_Controller->setGamePaused(true);
			break;
		case WM_ACTIVATEAPP: //Sent when any window is activated (both windows get this) 
			if (wParam == TRUE)
				_Controller->setGamePaused(false);
			else
				_Controller->setGamePaused(true);
			break;
		case WM_EXITSIZEMOVE:
			_Controller->setGamePaused(false);
			break;
		case WM_EXITMENULOOP:
			_Controller->setGamePaused(false);
			break;
        case WM_DESTROY:
            _Controller->setGameOver(true);
            //PostQuitMessage(0);
			break;
		default:
			break;
	}//end switch
	return 0;
}

LRESULT RawInputz::_prepareRawInput(HWND window, LPARAM lParam)
{
	//Get the _raw input to check its _buffer size, make sure its not greater than 40 (_bufferSize);
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &this->_checkBufferSize, sizeof (RAWINPUTHEADER));
	if (this->_checkBufferSize > this->_bufferSize) {
		MessageBox(window, TEXT("RAW INPUT ERROR! BUFFER SIZE TO BIG"), TEXT("BREAKPOINT"), 0);
		this->_Controller->setGameOver(true);
		//PostQuitMessage(0);
		return 0;
	}

	// Call the function again, this time with the _buffer to get the data
	/** This function takes a handle to the RAWINPUT structure from the device. This handle is provided for us in the lParam of the message so we just need to pass it on. 
	* The second parameter is either RID_INPUT to get the _raw device data (which we want) or RID_HEADER to get the header information for the data. 
	* The third parameter is a void pointer to the _buffer to be filled. If we want to just get the size needed for a _buffer we pass NULL in here. 
	* The next parameter is the address of a variable that will be filled by the function with the required size of the _buffer. 
	* The final parameter is always the same and is the size of the RAWINPUTHEADER structure. 
	* The function returns the number of bytes written into the structure so as a sanity check you can make sure this value matches with the _bufferSize you expected to get.
	*/
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, (LPVOID)_buffer, &_bufferSize, sizeof (RAWINPUTHEADER));

	/** Now that we have a _buffer filled with data from the device we need to interpret it based on what device it came from. 
	* We do this by casting it to a RAWINPUT structure and then reading the type from the header data.
	*/
	this->_raw = (RAWINPUT*) _buffer;

	if (this->_raw->header.dwType == RIM_TYPEKEYBOARD) {
		// read the keyboard data
		// The RAWINPUT structure also has a member called keyboard of type RAWKEYBOARD which, if the header type is RIM_TYPEKEYBOARD, will be filled with key information.
		// Get key value from the keyboard member (of type RAWKEYBOARD)
		this->_keyCode = this->_raw->data.keyboard.VKey;
		//check if the key is released
		this->_keyUp = this->_raw->data.keyboard.Flags & RI_KEY_BREAK;;
		this->_keyDown = this->_raw->data.keyboard.Flags & RI_KEY_MAKE;
	} else if (this->_raw->header.dwType == RIM_TYPEMOUSE) {
		/** Get values from the mouse member (of type RAWMOUSE)
		Note that the last position returned are not screen space values like you get from the WM_MOUSEMOVE message. 
		This is raw data we are getting so the values need interpreting. The values are normally relative to the 
		last position and hence indicate motion. To be sure you can check the usFlags in the RAWMOUSE structure.

		Example:
		lLastX = lLastY = +1 means the mouse moved bottom right (bizarro coordinate system)
		lLastX -1, lLast Y = 0 means you moved the mouse left but not up or down
		*/
		this->_lastMouseX = this->_raw->data.mouse.lLastX;
		this->_lastMouseY = this->_raw->data.mouse.lLastY;

		this->_mouseUp = this->_raw->data.mouse.ulButtons & RI_MOUSE_LEFT_BUTTON_UP;
		this->_mouseDown = this->_raw->data.mouse.ulButtons & RI_MOUSE_LEFT_BUTTON_DOWN;
	}
}

void RawInputz::releaseRawInputz()
{
	delete[] this->_buffer;
	this->_buffer = NULL;

	this->_raw = NULL;
	this->_Controller = NULL;

}

void RawInputz::_resetKeyPressed()
{
	this->_keyUp = true;
	this->_keyDown = false;
}

void RawInputz::_resetMousePressed()
{
	this->_mouseUp = true;
	this->_mouseDown = false;
}