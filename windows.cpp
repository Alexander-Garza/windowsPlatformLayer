#include <windows.h>

LRESULT CALLBACK MainWndProc(
		HWND hwnd,        // handle to window
		UINT uMsg,        // message identifier
		WPARAM wParam,    // first message parameter
		LPARAM lParam)    // second message parameter
{ 
	LRESULT result = 0;
	switch (uMsg) 
	{ 
		case WM_CREATE: 
			// Initialize the window. 
			break;

		case WM_PAINT: 
			// Paint the window's client area. 
			break;

		case WM_SIZE: 
			// Set the size and position of the window. 
			break;

		case WM_DESTROY: 
			// Clean up window-specific data objects. 
			break;

			// 
			// Process other messages. 
			// 

		default: 
			result = DefWindowProc(hwnd, uMsg, wParam, lParam); 
	} 
	return result; 
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSA windowClass = {};
	windowClass.style 			= CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	windowClass.lpfnWndProc 	= MainWndProc;
	windowClass.hInstance 		= hPrevInstance;
	windowClass.hCursor 		= LoadCursor(0, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	windowClass.hIcon         = LoadIcon(NULL,  IDI_APPLICATION);
	windowClass.lpszClassName = "windowClassName";
	ATOM windowClassIsRegistered = RegisterClassA(&windowClass);
	if(!windowClassIsRegistered)
	{
		// TODO: logging
		return 1;
	}
	unsigned int windowWidth = 1920;
	unsigned int windowHeight = 1080;
	HWND windowHandle = CreateWindowExA(
			0, 
			windowClass.lpszClassName, 
			"Application Name", 
			WS_OVERLAPPEDWINDOW, 
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			windowWidth, 
			windowHeight, 
			0, 
			0, 
			hPrevInstance, 
			0);
	if(!windowHandle)
	{
		// TODO: logging
		return 1;
	}
	unsigned int isRunning = true;
	while(isRunning)
	{
	}

	return 0;
}
