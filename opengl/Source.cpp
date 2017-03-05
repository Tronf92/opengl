#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/subsystem:windows")
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT paintStruct;

	HDC hDC;

	char string[]="Good Bye!";

	switch (message)
	{
		case WM_CREATE:
			return 0;
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
			break;
		case WM_PAINT:
			hDC = BeginPaint(hwnd, &paintStruct);
			SetTextColor(hDC,COLORREF(0x00FF0000) );
			TextOut(hDC,150,150,string,sizeof(string)-1);
			EndPaint(hwnd,&paintStruct);
			return 0;
			break;
		default:
			break;
	}
	return (DefWindowProc(hwnd,message,wParam,lParam));

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){

	WNDCLASSEX windowClass;
	HWND hwnd;
	MSG msg;
	bool done;


	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra= 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "MyClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&windowClass) ){
		return 0;
	}

	hwnd = CreateWindowEx(NULL, "MyClass","A Real Win App", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU,
							100,100,400,400,NULL,NULL, hInstance,NULL);

	if(!hwnd)
		return 0;
	done = false;

	while(!done)
	{
		PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE);
		if(msg.message == WM_QUIT ){
			done=true;
		}
		else{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}



