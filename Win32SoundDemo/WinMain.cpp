///
/// Winmain ����Ʈ
/// 
/// FMOD ���� ������ ���ؼ� ��������
/// 2022.02.18 ����ȯ

#include <windows.h>
//#include "..\SoundTest\CSoundManager.h"	// �̷��� �ᱹ ������ �˰� �ȴ�.
#include "..\SoundLib\InstanceGetter.h"		// �� �� ������ SoundLib.Lib (fmod.dll ���Ӽ� ����)
#include "..\SoundLib\ISoundManager.h"		// �� �� ������ SoundLib.Lib (fmod.dll ���Ӽ� ����)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// WinMain �Լ� : ������ ���α׷��� ���� ������ ( Entry Point )
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	char	  szAppName[] = "Game Academy 2022";
	HWND	  hWnd;
	MSG      msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	/// ���� Ŭ���� ���
	RegisterClass(&wndclass);

	/// ���� ����
	hWnd = CreateWindow(szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		100, 100, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	/// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	// ���� �Ŵ��� �׽�Ʈ
	ISoundManager* _pSoundManager = ::GetSoundManager();
	//CSoundManager* _pSoundManager = new CSoundManager();		// �̷��� �ᱹ ������ �˰� �ȴ�.
	_pSoundManager->Initialize();


	/// �޽��� ����
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			_pSoundManager->Update();

			if (GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				//_pSoundManager->
			}
		}
	}

	_pSoundManager->Finalize();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

