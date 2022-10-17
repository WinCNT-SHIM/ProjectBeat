//#include "GameProcess.h"
#include "GamePCH.h"
#include "GameProcess.h"
#include "EventSystem.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
GameProcess* _GameProcess = new GameProcess();
bool SetMonitorResolution(int xRes, int yRes, int depth, int frequecy);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	SetMonitorResolution(1920,1080,32,60);

	LPCWSTR szAppName = L"Beat";
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;

	UINT_PTR asdasd = 124351451;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;//
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	// 윈도 클래스 등록
	RegisterClass(&wndclass);
	int width = GetSystemMetrics(SM_CXSCREEN);
	int Height = GetSystemMetrics(SM_CYSCREEN);

	//윈도 생성
	hWnd = CreateWindow(szAppName, szAppName, WS_POPUP, 0, 0, width, Height, NULL, NULL, hInstance, NULL);
	//hWnd = CreateWindowEx(WS_EX_TOPMOST, szAppName, szAppName, WS_OVERLAPPEDWINDOW, 100, 000, 1920, 1080, NULL, NULL, hInstance, NULL);
	//생성된 윈도를 화면에 표시
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	
	_GameProcess->Initialize(hWnd);



	



	/// 메세지 루프
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);

		}
		else
		{
			_GameProcess->Update();
			_GameProcess->Render();
		}
	}
	delete _GameProcess;

	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	switch (message)
	{
	case WM_LBUTTONUP:
		if (EventSystem::Instance()) EventSystem::Instance()->OnLButtonUp(LOWORD(IParam), HIWORD(IParam));
		break;
	case WM_LBUTTONDOWN:
		if (EventSystem::Instance()) EventSystem::Instance()->OnLButtonDown(LOWORD(IParam), HIWORD(IParam));
		break;
	case WM_MOUSEMOVE:
		if (EventSystem::Instance()) EventSystem::Instance()->OnMouseMove(LOWORD(IParam), HIWORD(IParam));
		break;
	case WM_LBUTTONDBLCLK:
		if (EventSystem::Instance()) EventSystem::Instance()->OnLButtonClick(LOWORD(IParam), HIWORD(IParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, IParam);
	}
	return 0;
}


bool SetMonitorResolution(int xRes, int yRes, int depth, int frequecy)
{
	DEVMODE             deviceMode;
	DISPLAY_DEVICE      displayDevice;
	memset(&displayDevice, 0, sizeof(DISPLAY_DEVICE));
	memset(&deviceMode, 0, sizeof(DEVMODE));
	displayDevice.cb = sizeof(displayDevice);

	//i번째 모니터의 디바이스 정보를 얻어옴
	EnumDisplayDevices(NULL, 0, &displayDevice, 0);
	//디바이스 이름을 가지고 현재 화면 정보를 얻음
	EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &deviceMode);

	// 해상도를 바꿈
	deviceMode.dmBitsPerPel = depth;
	deviceMode.dmPelsWidth = xRes;
	deviceMode.dmPelsHeight = yRes;
	deviceMode.dmDisplayFrequency = frequecy;
	deviceMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettingsEx(displayDevice.DeviceName, &deviceMode, NULL, CDS_TEST, NULL) == DISP_CHANGE_SUCCESSFUL)
		ChangeDisplaySettingsEx(displayDevice.DeviceName, &deviceMode, NULL, 0, NULL);
	else
		return false;
	return true;
}
