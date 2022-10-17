#pragma once
// Direct 2D Header
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <dwrite.h> // DirectWrite
#include <wincodec.h> // WIC(Windows Imaging Component)

// Direct 2D Library �߰�
// ������Ʈ - �Ӽ����ε� �߰��� �� ������
// �׷��Ƚ� ���������� ����ϴ� ���̱� ������ �ڵ�� �߰��Ѵ�
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment (lib, "WindowsCodecs.lib") //WIC

//#include <windows.h> //Macro�� ����
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <iostream>

/// <summary>
/// MSDN�� �ִ� ���� �ڵ�
/// null üũ�� �ؼ� �޸𸮸� �����Ѵ�
/// </summary>
/// <typeparam name="Interface"></typeparam>
/// <param name="ppInterfaceToRelease"></param>
template<typename Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease)
    {
        (*ppInterfaceToRelease)->Release();
        *ppInterfaceToRelease = nullptr;
    }
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif