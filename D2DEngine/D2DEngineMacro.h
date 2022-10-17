#pragma once
// Direct 2D Header
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <dwrite.h> // DirectWrite
#include <wincodec.h> // WIC(Windows Imaging Component)

// Direct 2D Library 추가
// 프로젝트 - 속성으로도 추가할 수 있지만
// 그래픽스 엔진에서만 사용하는 것이기 때문에 코드로 추가한다
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment (lib, "WindowsCodecs.lib") //WIC

//#include <windows.h> //Macro에 존재
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <iostream>

/// <summary>
/// MSDN에 있는 해제 코드
/// null 체크를 해서 메모리를 해제한다
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