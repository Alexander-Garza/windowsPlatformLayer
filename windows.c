#include <windows.h>

unsigned int isRunning = 1;

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

		//case WM_PAINT: 
			// Paint the window's client area. 
			//break;

		case WM_SIZE: 
			// Set the size and position of the window. 
			break;

		case WM_DESTROY:
			isRunning = 0;
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
	WNDCLASSA windowClass = {0};
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
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);

	MSG message;
	while(isRunning)
	{
		// Process Input Messages //
		while(1)
		{
			BOOL gotMessage = FALSE;
			// NOTE: We don't want to handle WM_PAINT messages here
			gotMessage = PeekMessage(&message, 0, 0, WM_PAINT -1, PM_REMOVE);
			if(!gotMessage)
			{
				gotMessage = PeekMessage(&message, 0, WM_PAINT+1, 0xFFFFFFFF, PM_REMOVE);
			}
			if(!gotMessage)
			{
				break;
			}
			switch(message.message)
			{
				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
				case WM_KEYDOWN:
				case WM_KEYUP:
					unsigned int keyCode = (unsigned int)message.wParam;
					unsigned int altKeyWasDown = (message.lParam & (1 << 29));
					unsigned int wasDown = ((message.lParam & (1 << 30)) != 0);
					unsigned int isDown = ((message.lParam & (1 << 31)) == 0);
					if(wasDown != isDown)
					{
						if(isDown)
						{
							if((keyCode == VK_F4) && altKeyWasDown)
							{
								isRunning = 0;
							}
						}
						else if(wasDown)
						{
						}
					}
					break;
				default:
					// NOTE: The rest we send to callback function
					TranslateMessage(&message);
					DispatchMessageA(&message);
					break;
			}
		}
	}

	return 0;
}
