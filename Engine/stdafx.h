#pragma once
/// <summary>
/// 미리 컴파일된 헤더(PCH)
/// 
/// 추가 방법
/// 1. stdafx.h, stdafx.cpp 추가
/// 2. 프로젝트 - 속성 - C/C++ - 미리 컴파일된 헤더 - 미리 컴파일된 헤더 "사용" 선택
/// 3. stdafx.cpp - 속성 - C/C++ - 미리 컴파일된 헤더 - 미리 컴파일된 헤더 "만들기" 선택
/// 4. stdafx.cpp에 #include "stdafx.h" 추가
/// 5. stdafx.h에 필요한 헤더들을 기술
/// 
/// 변경이 적고 빈번하게 사용되는 헤더만 기술할 것!
/// 2022.02.07 심승수
/// </summary>



// Windows Header Files:
#include <windows.h>
// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <cmath>
#include <string>
#include <tchar.h>

// 기본 direct2D api 헤더
// 아래 헤더들은 그래픽에만 사용되는 헤더라 그래픽스 엔진으로 옮김
// c++ 도우미 함수, 클래스 및 구조
//#include <d2d1helper.h>
// text
//#include <dwrite.h>
//#include <wincodec.h>
// image
//#include <wincodec.h>
//#include "d2d1effects_2.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Output\\Debug\\D2DEngine.lib")
#pragma comment(lib, "..\\Output\\Debug\\Resource.lib")
#else
#pragma comment(lib, "..\\Output\\Release\\D2DEngine.lib")
#pragma comment(lib, "..\\Output\\Release\\Resource.lib")
#endif


#include <map>
#include <vector>
#include <algorithm>
#include <assert.h>

#include "DeBugPrint.h"
#include "CTime.h"
#include "CBase.h"

#include "GameObject.h"
#include "Physics.h"
#include "CPlayerInput.h"
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
#include "Renderer.h"

#include "D2DEngine.h"

//#pragma comment(lib, "dwrite.lib")
//#pragma comment(lib, "Windowscodecs.lib")

using namespace std;

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