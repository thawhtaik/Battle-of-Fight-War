#include "DirectXStuff.h"

/** Direct3D stuff (I = interface functions)
    They're just like any classes you have written; they provide an interface to do shit with!
	Hang in there, Thaw! */

DirectXStuff GlobalDirectXStuff;

/** Constructor */
DirectXStuff::DirectXStuff()
{
	//set all devices to NULL!
	d3d = NULL;
    d3ddev = NULL;

	backbuffer = NULL;
	surface = NULL;

	spriteObj = NULL;
}

/** Game initialization function; register class, create the window using the handle here 

FOR INFORMATION ON D3D RESOURCES GO HERE
http://www.toymaker.info/Games/html/d3d_resources.html



*/
bool DirectXStuff::initDirectXStuff(HWND window, int newScreenWidth, int newScreenHeight, bool fullScreen)
{
    /** Create object pointer (easy!) -----------------------------------------------------------------*/
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    if (d3d == NULL) {
        MessageBox(window, TEXT("Error initializing Direct3D Interface"), TEXT("Error"), MB_OK);
		Debugger.print("Error initializing Direct3D Interface");
        return 0;
    }

	//Check that the Device supports what we need from it
	D3DCAPS9 caps;
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	//Hardware Vertex Processing or not?
	int VERTEX_PROCESSING = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		VERTEX_PROCESSING = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		VERTEX_PROCESSING = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//Check vertex & pixelshader versions
	if (caps.VertexShaderVersion < D3DVS_VERSION(2, 0) || caps.PixelShaderVersion < D3DPS_VERSION(2, 0)) {
		Debugger.print("Warning - Your graphic card does not support vertex and pixelshaders version 2.0");
	}
     
/** Create device pointer (Gay!) ------------------------------------------------------------------*/

//Must first create presentation parameters (initially 0)

//PRESENTATION PARAMETERS -------------------------------------------------------------------------------------------

	/** Presentation parameter stuff, first default everything to 0, then set necessary params for a windowed game */
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp)); //defaulting everything to zero
    d3dpp.Windowed = (!fullScreen);
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //Allows video card to control swapping of backbuffer and render target
	
	/** Added in multisampling stuff to see if it works */
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	/** BackbufferFormat - D3DFMT_UNKNOWN is used when running in a window and means Direct3D will use the current 
	display mode format (whatever bit depth, resolution you currently have your desktop set to). */
    //d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = 0; //Using 0 for BackBuffer width and height here so crap doesn't get rescaled
    d3dpp.BackBufferHeight = 0; //while using windowed mode
    d3dpp.hDeviceWindow = window;

	/** 
	PresentationInterval - how often the back buffer is copied to the front buffer. D3DPRESENT_INTERVAL_ONE 
	(the default) will cause this to synchronise with the monitor refresh - hence avoiding tearing effects. 
	D3DPRESENT_INTERVAL_IMMEDIATE causes the copy to occur as soon as the card has finished rendering.
	*/
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	 
	/** For the z buffer!
	EnableAutoDepthStencil - if set to TRUE Direct3D will create and manage depth buffers for your game. 
	As mentioned stencil and depth buffers are often combined so this creates the facility to use 
	both. If this is TRUE you must also define:
	*/
	d3dpp.EnableAutoDepthStencil = false;

	/** Also For the z buffer!
	AutoDepthStencilFormat - allows you to specify the format of the buffer in terms of how many bits 
	are used to store each value. Beware that certain graphic modes will not allow you to specify 
	anything better than a 16 bit format. Generally you use D3DFMT_D16
	*/
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Flags = 0;

//DONE SETTING PRESENTATION PARAMETERS --------------------------------------------------------------------------------

    /** Create the fucking device pointer with all of the above presentation params; refer to above for arguments
	The code is of type HRESULT
	The API provides you with two macros that you can use to determine the success of the call. 
	The two macros are SUCCEEDED and FAILED. Be careful not to test against true and false, you must use the macros.

	adapter - index of adapter (video card) you wish to use; D3DADAPTER_DEFAULT is primary adapter
	device type - member of d3ddevtype enum (hardware or software driver); normally use hardware driver 3DDEVTYPE_HAL
	focus window - the window handle the device is to be associated with
	behavior flags - combo of flags; important flags control whether VertexStruct processing is hardware or software driven
	presentation parameters - default is 0 for windowed mode; how the rendered scene is presented

	Some important behavior flags you can use (in combo if you want)
	D3DCREATE_HARDWARE_VERTEXPROCESSING - this means that the video card should handle VertexStruct calculations. This is the fastest method but requires support from the hardware.
	D3DCREATE_SOFTWARE_VERTEXPROCESSING - this means that Direct3D handles VertexStruct processing itself so no video card acceleration is used. This is obviously slower than using hardware.
	D3DCREATE_MIXED_VERTEXPROCESSING - this means that both the hardware and software are used for VertexStruct processing. This can be useful if your video card does not support the full set of accelerated processing required.
*/
    d3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        window,
        VERTEX_PROCESSING,
        &d3dpp,
        &d3ddev
    );
     
    if (d3ddev == NULL) {
        MessageBox(window, TEXT("Error creating Direct3D device"), TEXT("Error"), MB_OK);
		Debugger.print("Error creating Direct3D device");
        return 0;
    }

	/**
	Sampling is the process of taking values from an input at regular intervals. The more values we take the more 
	accurate the resultant representation.
	It is important to remember that we are rendering our graphics onto a finite sized grid of pixels (the size 
	of the grid is the screen resolution) and it is this restriction that can cause problems. E.g. if you render 
	a 16 by 16 texture onto an object that is close up to the camera it may actually take up 100 by 100 screen 
	pixels and so will need to be stretched. The effect will be a horrible blocky texture. To solve this we can 
	apply filtering techniques like bilinear filtering.

	The params for setSamplerState are as follows:
	Sampler - the sampler stage index (you can have a number of stages)
	State - this is a flag representing one of states that you want to change.
	Value - each state can have a value. What goes here depends totally on the State value.

	Some States:
	D3DSAMP_MAGFILTER - if the texture is rendered larger than its created size it will look blocky. We can 
		improve the look by setting a filter, choices are D3DTEXF_POINT where the closest texel is chosen, 
		D3DTEXF_LINEAR which applies bilinear filtering (a method where a weighted average of the 2 by 2 texels 
		surrounding the pixel is used) , D3DTEXF_ANISOTROPIC which takes into account the angle a primitive is 
		rendered, D3DTEXF_PYRAMIDALQUAD which takes 4 samples and uses a tent filter and D3DTEXF_GAUSSIANQUAD 
		which also takes 4 samples but uses a Gaussian filter.
	D3DSAMP_MINFILTER - if the texture is rendered smaller than its created size crawling effects and other nasty 
		artefacts can occur. To solve this we can apply the same filters as above.
	D3DSAMP_MIPFILTER - mip maps can be used to both improve the look of textures and reduce the data size being 
		rendered. When you supply the texture you also supply a chain of textures of different sizes. When 
		rendering Direct3D chooses the size that is closest to the screen size the texture is rendered at. This 
		can be improved further by filtering between the two mip map textures each side of the correct size. This 
		value defines that filter - the choices are the same as for the magnification filter.

	*/
	/*this->d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	this->d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	this->d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);*/

	/** Device pointer created ------------------------------------------------------------------------- */

	/** Once you have obtained your device pointer you can use it to display graphics. The render loop will always 
	be the same:

    1. Clear the current contents
    2. Tell the device you are beginning to render
    3. Render your scene
    4. Tell the device you have finished rendering
    5. Present the scene (display it). */

	/** Create back buffer (easy) and surface pointer + other surface shit -----------------------------------------------*/
	//Get the backbuffer (read by the frame buffer; better to write to backbuffer than directly to framebuffer)
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	//Create surface (offscreen / secondary; in memory, it looks like a bitmap - a header followed by data representing pixels)
	HRESULT result = d3ddev->CreateOffscreenPlainSurface(
	    16, //width of surface
		16, //height of surface
		D3DFMT_X8R8G8B8, //surface format
		D3DPOOL_DEFAULT, //memory pool to use
		&surface, //pointer to the surface
		NULL //reserved; always NULL actually
	);

	if (!SUCCEEDED(result)) {
		MessageBox(window, TEXT("Error creating Direct3D surface"), TEXT("Error"), MB_OK);
		Debugger.print("Error creating Direct3D surface");
		return false;
	}

	// Now do sprite stuff---------------------------------------------------------------------------------------------------------

	//Create the sprite object; this sprite object draws sprites to the backbuffer
	D3DXCreateSprite(d3ddev, &spriteObj);

	//--------------------------------------------------------------------------------------------------------------------

	//MessageBox(window, TEXT("Game Init successful"), TEXT("BREAKPOINT"), 0);
	Debugger.print("DirectX initiation successful");

	//clear the backbuffer to black
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0),1.0f,0);

	if (this->d3d) { //This is actually no longer needed; just the device
		this->d3d->Release();
		this->d3d = NULL;
	}

    return true;

}//end gameInit

/** Game shutdown function */
void DirectXStuff::releaseDirectXStuff()
{
	 //free memory; D3D DEVICE AND OBJECT MUST BE RELEASED LAST
	if (spriteObj) {
		spriteObj->Release();
		spriteObj = NULL;
	}
	if (surface) {
		surface->Release();
	    surface = NULL;
	}
	if (backbuffer) {
		backbuffer->Release();
	    backbuffer = NULL;
	}
	if (d3ddev) {
		d3ddev->Release();
	    d3ddev = NULL;
	}
    if (d3d) { //Shouldn't need to do this but just in case
		d3d->Release();
	    d3d = NULL;
	}

	Debugger << "DirectX shutdown successful";
     
}//end releaseGame

/** Guess I shoulda done this one a long time ago (lol?) 

The Z buffer is filled each render loop. It is filled with values ranging from 0.0f (as close as you can get) 
to 1.0f (as far away as you can get). At the beginning of each render loop we need to clear the buffer to 1.0f 
ready for the next render.

This time we are specifying that we want to clear both the target (D3DCLEAR_TARGET) and the z buffer (D3DCLEAR_ZBUFFER).
We are clearing the screen to white and the z buffer to 1.0f (as far away as you can get). The final value in this call
is where you could specify a value to clear the stencil buffer to.

That is all there is to enabling a z buffer in Direct3D. After the above process the Z buffer will be used 
automatically by Direct3D.

*/
void DirectXStuff::clearScene(D3DXCOLOR color)
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

/** Load the given bitmap file into a surface; returns a pointer to said surface */
LPDIRECT3DSURFACE9 DirectXStuff::loadSurface(string bitmapName)
{
	LPDIRECT3DSURFACE9 image = NULL;

	//Get width and height of bitmap file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(bitmapName.c_str(), &info);

	if (result != D3D_OK) { //Unsuccessful
		return NULL;
	}

	//Create a surface for the image
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width, //surface height
		info.Height, //surface width
		D3DFMT_X8R8G8B8, //image format
		D3DPOOL_DEFAULT, //memory pool to use
		&image, //pointer to surface
		NULL //reserved (always NULL)
	);

	if (result != D3D_OK) {
		return NULL;
	}

	//load bitmap file into the surface we just created
	result = D3DXLoadSurfaceFromFile(
		image, //Destination surface
		NULL, //destination palette
		NULL, //destination rectangle
		bitmapName.c_str(), //source bitmap file name
		NULL, //source rectangle
		D3DX_DEFAULT, //controls how image is filtered
		D3DCOLOR_XRGB(0, 0, 0), //for transparancy (0 for none)
		NULL); //source image info (usually NULL)

	//make sure file was loaded okay
	if (result != D3D_OK) { 
		return NULL;
	}

	return image;
}

/** Load a texture given the bitmap name, return texture pointer
    transcolor is the transparent color for the sprite (usually hotpink (255,0,255))
	
D3DXCreateTextureFromFile automatically converts the texture into a correct format for your device
(the video card when in hardware mode). 
The following file formats are supported: bmp, .dds, .dib, .jpg, .png, and .tga. 
Mipmaps are loaded (in .dds files) and alpha if present (supported by .tga and .dds files amongst 
others). The texture memory allocation is left to Direct3D to handle – it will place it in the best 
place possible.
	
*/
LPDIRECT3DTEXTURE9 DirectXStuff::loadTexture(string bitmapName, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;

	//get width and height from bitmap file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(bitmapName.c_str(), &info);

	if (result != D3D_OK) {
		return NULL;
	}

	//create the new texture by loading a bitmap image file
	D3DXCreateTextureFromFileEx(
	    d3ddev, //Direct3D device object
		bitmapName.c_str(), //bitmap filename
		info.Width, //bitmap image width
		info.Height, //bitmap image height
		1, //Mip-map (WTF?) levels
		D3DPOOL_DEFAULT, //type of surface (standard)
		D3DFMT_UNKNOWN, //surface format (default)
		D3DPOOL_DEFAULT, //memory class for the texture
		D3DX_DEFAULT, //image filter
		D3DX_DEFAULT, //mip filter
		transcolor, //color key for transparency
		&info, //bitmap file info (from loaded file)
		NULL, //color palette
		&texture //destination texture
	);

	//make sure bitmap texture was loaded correctly!
	if (result != D3D_OK) {
		return NULL;
	}

	return texture;
}

/** Draw a surface to the screen given the source and destination surfaces; uses StretchRect
    x, y are the points you want to draw at (top-left of rectangle) 
	Note that this uses the size of the source surface to determine how big you want to draw */
void DirectXStuff::drawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source)
{
	//get width and height of source surface
	//useful so you only need to define source surface width / height when creating it rather than keeping track
	D3DSURFACE_DESC desc;
	source->GetDesc(&desc);

	//rectangles for drawing; note destination rectangle is equal size to source rectangle
	//apparently you can define them like enum; are they structs?
	RECT source_rect = {0, 0, (long)desc.Width, (long)desc.Height};
	RECT dest_rect = {(long)x, (long)y, (long)x + desc.Width, (long)y + desc.Height};

	//draw the source surface on to the destination
	d3ddev->StretchRect(source, &source_rect, dest, &dest_rect, D3DTEXF_NONE);	
}//end drawSurface


void DirectXStuff::drawTile(
	LPDIRECT3DSURFACE9 SourceSurface, //source surface image
	int tileNumber, //tileNumber on the spriteSheet
	int tileWidth,
	int tileHeight,
	int numberOfColumns, //number of tile columns
	LPDIRECT3DSURFACE9 DestinationSurface, //destination surface
	int destinationX,  //x coords of where to draw
	int destinationY //y coords of where to draw
)
{
	//Create rectangle to describe source surface image
	RECT sourceRectangle;
	sourceRectangle.left = (tileNumber % numberOfColumns) * tileWidth;
	sourceRectangle.top = (tileNumber / numberOfColumns) * tileHeight;
	sourceRectangle.right = sourceRectangle.left + tileWidth;
	sourceRectangle.bottom = sourceRectangle.top + tileHeight;

	//Set destination rectangle
	RECT destinationRectangle = {destinationX, destinationY, destinationX + tileWidth, destinationY + tileHeight};

	//Actually draw the damn tile
	this->d3ddev->StretchRect(SourceSurface, &sourceRectangle, DestinationSurface, &destinationRectangle, D3DTEXF_NONE);
}


void DirectXStuff::drawRectangle(int x1, int y1, int x2, int y2, enum color c)
{
	int r,g,b;
	r = 0;
	g = 0;
	b = 0;
	//set the RGB values appropriately given the color
	switch(c)
	{
	    case BLACK:
			//lol nothing
			break;
		case RED:
			r = 255;
			break;
		case GREEN:
			g = 255;
			break;
		case BLUE:
			b = 255;
			break;
		case CYAN:
			break;
		case MAGENTA:
			break;
		case YELLOW:
			r = 255;
			g = 255;
			break;
		case WHITE:
			r = g = b = 255;
			break;
	}
	//Fill color
	d3ddev->ColorFill(
	    surface, //surface to fill 
		NULL, //rectangle to fill
		D3DCOLOR_XRGB(r,g,b) //color (format uses ints i guess)
	);

	//Set rectangle coords
	rect.left = x1;
	rect.right = x2;
	rect.top = y1;
	rect.bottom = y2;

	//Bitblock transfer ("Blit" surface to screen)
	d3ddev->StretchRect(
	    surface, //source surface
		NULL, //source rect
		backbuffer, //destination surface
		&rect, //destination rectangle
	    D3DTEXF_NONE //filter
	); 

}//end drawRectangle

/** It's better if everything that needs a sprite object has its own */
LPD3DXSPRITE DirectXStuff::getNewSpriteObject()
{
	LPD3DXSPRITE NewSpriteObject = NULL;
	D3DXCreateSprite(this->d3ddev, &NewSpriteObject);

	return NewSpriteObject;
}

/** Draw a transformed sprite; does all the matrix shit for you */
void DirectXStuff::spriteTransformDraw(LPDIRECT3DTEXTURE9 texture, int x, int y, int frameWidth, int frameHeight, D3DCOLOR color, int currentFrame, int columns, float rotation, float scaling)
{
	//Create 2D vectors for scale and translate values (indicate scale x-wise and y-wise)
	D3DXVECTOR2 scale(scaling, scaling);
	D3DXVECTOR2 translate(x, y);

	//Set center by dividing width and height by 2, take scaling into account
	D3DXVECTOR2 center((float)(frameWidth * scaling)/2, (float)(frameHeight * scaling)/2);

	//The 2D transformation matrix and the function that actually sets the matrix values
	D3DXMATRIX mat;

	D3DXMatrixTransformation2D(
		&mat, //The matrix; note pass by reference 
		NULL, //scaling center point (not used)
		0, //scaling rotation value (not used)
		&scale, //scaling vector
		&center, //rotation / pivot center
		rotation, //rotation angle
		&translate //translation vector
	); 

	//Tell sprite object to use the matrix
	spriteObj->SetTransform(&mat);

	//calculate frame location in source image (only useful if it's a spritesheet)
	int fx = (currentFrame % columns) * frameWidth;
	int fy = (currentFrame / columns) * frameHeight;
	RECT sourceRect = {fx, fy, fx + frameWidth, fy + frameHeight};

	//Draw the sprite frame; note we are not filling in pivot center or position because those are already set 
	//by the matrix
	spriteObj->Draw(texture, &sourceRect, NULL, NULL, color);

	/** More on spriteObj->Draw
	pSrcTexture - a pointer to the texture to be used, see textures
	pSrcRect - pointer to a rectangle defining the area of the texture to use or NULL for the whole texture
	pCenter- pointer to a 3D vector specifying the position in the sprite around which it can be rotated or 
		NULL for top left
	pTranslation - pointer to a 3D vector defining the screen position of the sprite. Note: in Direct3D 0,0 
		is the top left of the screen.
	Color - colour value that can be used to modulate the texture colours. A value of 0xFFFFFFFF maintains 
		the colour from the texture. Note: you can use the D3DCOLOR_COLORVALUE macro to create a D3DCOLOR 
		from RGB values.
	*/

}//end spriteTransformDraw

/** Creates and returns a pointer to a font object

Direct3D comes with a set of interfaces to help you easily draw text to the screen. It is worth knowing how it does it 
before using it. This is the traditional method used by games developers:

Create a texture containing all the letters in the alphabet and numbers etc.
Store the position of each letter in this texture (U,V texture co-ordinates)
When text needs to be displayed create a screen QuadStruct comprising two triangles at the correct position
Set the UV co-ordinates to the correct position in the font texture for the required character
Repeat for all letters in the word

Direct3D provides a set of interfaces that can do all this for you. It may not be the fastest method in the world so 
developers do normally create their own (as described above) but it will do perfectly well to start with.

The D3DXCreateFont function creates a Windows 32 font and uses that to create its characters. This means there are a 
lot of parameters to this function call allowing a font to be specified. You can look in the DirectX help and at the 
Windows 32 CreateFont function for the list of parameters. 

*/
LPD3DXFONT DirectXStuff::makeFont(string fontName, int fontSize)
{
	LPD3DXFONT font = NULL;

	D3DXFONT_DESC FontDescriptor = { //Font descriptor
		fontSize, //height
		0, //width
		0, //weight
		0, //miplevels
		false, //italic?
		DEFAULT_CHARSET, //character set
		OUT_TT_PRECIS, //output precision?
		CLIP_DEFAULT_PRECIS, //quality
		DEFAULT_PITCH, //pitch and family?
		"" //font name
	};

	strcpy(FontDescriptor.FaceName, fontName.c_str()); //convert string data to c-style array
	D3DXCreateFontIndirect(d3ddev, &FontDescriptor, &font);
	return font;
}

/** Use a given font object to draw text at location (x,y) in a certain color */
void DirectXStuff::fontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color)
{
	//Figure out the text boundary first
	RECT Rect = {x, y, 0, 0};

	/** 
	int DrawText( LPD3DXSPRITE pSprite, LPCTSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color );

	pSprite - the first parameter allows a sprite interface to be passed in. Setting this to NULL means Direct3D 
		will use its own internal sprite object to render the text. If you are doing lots of DrawText calls passing 
		your own sprite object can SPEED UP RENDERING SIGNIFICANTLY (Up to 4x - see font drawing optimisations).
	pString - this is the string to render. The type of string depends on your projects character set.
	Count -  the number of characters in the string. You can set this to the magic number -1 in order to specify that 
		Direct3D should count the characters itself. Note that this only works with null terminated strings.
	pRect - the rectangular area in which the text will be displayed. How the text is justified within this rectangle 
		depends on the next parameter:
	Format - allows you to specify some flags. This allows you to specify the justification of the text within the 
		rectangle plus some other options (see advanced).
	Color - the final parameter is the colour you want to render the text.
	As always you must release the D3DX interface before your program exits or on a device reset:

	*/
	//This call fills in values for rect (alternatively you could just fill in rect yourself)
	font->DrawText(this->spriteObj, text.c_str(), text.length(), &Rect, DT_CALCRECT, color);

	//Now print the text actually
	//Create vectors for matrix transformation (annoying)
	D3DXVECTOR2 scale(1, 1);
	D3DXVECTOR2 translate(x, y);
	D3DXVECTOR2 center((float)(Rect.right)/2, (float)(Rect.bottom));

	//The 2D transformation matrix and the function that actually sets the matrix values
	D3DXMATRIX mat;

	D3DXMatrixTransformation2D(
		&mat, //The matrix; note pass by reference 
		NULL, //scaling center point (not used)
		0, //scaling rotation value (not used)
		&scale, //scaling vector
		&center, //rotation / pivot center
		0, //rotation angle
		&translate //translation vector
	); 

	//Tell sprite object to use the matrix
	this->spriteObj->SetTransform(&mat);
	font->DrawText(this->spriteObj, text.c_str(), text.length(), &Rect, DT_LEFT, color);
}

//----------------- WHOA HOLY COW 3D SHIT ------------------------------

/**

Direct3D requires 3 matrices to be set before 3D geometry can be rendered. These matrices are used to transform the 
3D geometry from its initial definition in model space into the final image drawn on the screen in 2D screen space.

The steps the geometry goes through are:

1) You initially define your 3D object in an editor (like 3DS max) or by hard coding the values. You normally set 0,0,0 
as the centre of your object with VertexStruct positions defined relative to the centre. These positions are defined in ModelStruct 
Space
2) We want to position, rotate and scale our 3D model into our game world. In order to do this we must provide a matrix 
that Direct3D can use to convert the VertexStruct positions from model space into this new space, known as World Space. This 
matrix is called the World Matrix
3) We need the world to be transformed so it appears as if it is being viewed from a certain position in our world. This 
position is the location of the eye or camera. So we provide a matrix that allows Direct3D to convert from World Space 
into View Space (sometimes known as camera space). This matrix is called the View Matrix
4) Finally we need to tell Direct3D how to project this 3D View Space onto our flat 2D screen. So we provide a matrix 
that allows Direct3D to convert from View Space into Screen Space. This matrix is known as the Projection Matrix.

So the three matrix:

World Matrix - Transforms 3D data from ModelStruct Space into World Space. You need to set this before rendering every entity in your world.
View Matrix - Transforms from World Space into View Space. You need to set this each time your camera changes position
Projection Matrix - Transforms from View Space into Screen Space. You normally set this just once during initialization.

Direct3D uses a left handed system where X is right, Y up and Z in to the screen

SO IN A NUTSHELL:

The world matrix needs to be set to position every entity you render
The view matrix is set each time the camera changes position or orientation
The projection matrix is set just once at the start of your game

*/

/**

Sets the world matrix to identity

*/
void DirectXStuff::resetWorldMatrix()
{
	D3DXMATRIX worldTransformationMatrix;
	D3DXMatrixTranslation(&worldTransformationMatrix, 0.0f, 0.0f, 0.0f);
	d3ddev->SetTransform(D3DTS_WORLD, &worldTransformationMatrix); //D3DTS_WORLD: Identifies the transformation matrix being set as the world transformation matrix.
}

/**

TRANSLATE THE WORLD MATRIX to a point

*/
void DirectXStuff::translateWorldMatrix(float x, float y, float z)
{
	D3DXMATRIX worldTransformationMatrix;
	D3DXMatrixTranslation(&worldTransformationMatrix, x, y, z);
	d3ddev->SetTransform(D3DTS_WORLD, &worldTransformationMatrix);
}

/**

SETS THE VIEW MATRIX

*/
void DirectXStuff::setCamera(float x, float y, float z, float xLookAt, float yLookAt, float zLookAt)
{
	D3DXMATRIX viewMatrix;
	D3DXVECTOR3 UpDirection(0.0, 1.0f, 0.0f); //set y as up direction

	//move camera
	CameraLocation.x = x;
	CameraLocation.y = y;
	CameraLocation.z = z;

	//point camera
	CameraTarget.x = xLookAt;
	CameraTarget.y = yLookAt;
	CameraTarget.z = zLookAt;

	D3DXMatrixLookAtLH(&viewMatrix, &CameraLocation, &CameraTarget, &UpDirection); //Builds a left-handed look-at matrix; returns 1st param (matrix) as result
	/** Uses the following formula to construct returned matrix (so figure out what the fuck this means)
		zaxis = normal(At - Eye)
		xaxis = normal(cross(Up, zaxis))
		yaxis = cross(zaxis, xaxis)
    
		 xaxis.x           yaxis.x           zaxis.x          0
		 xaxis.y           yaxis.y           zaxis.y          0
		 xaxis.z           yaxis.z           zaxis.z          0
		-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1
	*/

	this->d3ddev->SetTransform(D3DTS_VIEW, &viewMatrix);
}

/**

Sets the PROJECTION MATRIX

*/
void DirectXStuff::setPerspective(float fieldOfView, float aspectRatio, float nearRange, float farRange)
{
	//Set perspective so things in distance will look smaller
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, fieldOfView, aspectRatio, nearRange, farRange); //Builds a left-handed perspective projection matrix based on a field of view.
	/** Again, that first matrix is the result; this is the formula 
		xScale     0          0               0
		0        yScale       0               0
		0          0       zf/(zf-zn)         1
		0          0       -zn*zf/(zf-zn)     0
		where:
		yScale = cot(fovY/2)

		xScale = yScale / aspect ratio
	*/
	this->d3ddev->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}

//Mesh stuff - File reading! ----------------------------------------------------------------------------------

void DirectXStuff::splitPath(const string &inputPath, string *pathOnly, string *fileNameOnly) {

	string fullPath(inputPath);

	replace(fullPath.begin(), fullPath.end(), '\\', '/'); //this method comes from <algorithm>
	string::size_type lastSlashPosition = fullPath.find_last_of('/');

	//Check if there's no path elements in input (just the file name on its own)
	if (lastSlashPosition == string::npos) {
		*pathOnly = "";
		*fileNameOnly = fullPath;
	} else {
		if (pathOnly) {
			*pathOnly = fullPath.substr(0, lastSlashPosition);
		}

		if (fileNameOnly) {
			*fileNameOnly = fullPath.substr(lastSlashPosition + 1, fullPath.size() - lastSlashPosition - 1);
		}
	}
}

bool DirectXStuff::doesFileExist(const string &fileName)
{
	return (_access(fileName.c_str(), 0) != -1); //accessMode 00 checks for existence only
}

bool DirectXStuff::findFile(string *fileName)
{
	if (!fileName) {
		return false;
	}

	//look for file using original file name and path
	if (this->doesFileExist(*fileName)) {
		return true;
	}

	//file not found, so try removing path (this is a bleedin' pain in the ass)
	string pathOnly;
	string fileNameOnly;
	this->splitPath(*fileName, &pathOnly, &fileNameOnly); //hopefully it doesn't get here!

	//is file found in current folder, without path?
	if (this->doesFileExist(fileNameOnly)) {
		*fileName = fileNameOnly;
		return true;
	}

	//Okay it makes much more sense now but AAAAAAAAAAAAAAAAAAAAAGGGGGHHHH
	//not found
	return false;
}

//Ugh
DWORD DirectXStuff::floatToDWord(float f)
{
	return *((DWORD*)&f);
}