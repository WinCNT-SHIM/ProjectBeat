#include "GameProcess.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GameProcess* testgame;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{
	char szAppName[] = "Game Academy 2021";
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
	wndclass.lpszClassName = szAppName;//

	// 윈도 클래스 등록
	RegisterClass(&wndclass);




	//윈도 생성

	hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, 100, 000, 1500, 1000, NULL, NULL, hInstance, NULL);


	testgame = new GameProcess();
	testgame->Initialize(hWnd);

	//생성된 윈도를 화면에 표시
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



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
			testgame->Update();
			testgame->Render();
		}
	}




	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	

	switch (message)
	{
	case WM_SIZE:
	{
		// 창 사이즈가 변경되면 렌더타겟을 다시 설정해줍니다.
		UINT _width = LOWORD(IParam);
		UINT _height = HIWORD(IParam);
		testgame->GetEngine()->OnResize(_width, _height);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, IParam);
	}
	return 0;
}