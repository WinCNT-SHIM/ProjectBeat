#pragma once
/// <summary>
/// �̸� �����ϵ� ���(PCH)
/// 
/// �߰� ���
/// 1. stdafx.h, stdafx.cpp �߰�
/// 2. ������Ʈ - �Ӽ� - C/C++ - �̸� �����ϵ� ��� - �̸� �����ϵ� ��� "���" ����
/// 3. stdafx.cpp - �Ӽ� - C/C++ - �̸� �����ϵ� ��� - �̸� �����ϵ� ��� "�����" ����
/// 4. stdafx.cpp�� #include "stdafx.h" �߰�
/// 5. stdafx.h�� �ʿ��� ������� ���
/// 
/// ������ ���� ����ϰ� ���Ǵ� ����� ����� ��!
/// 2022.02.07 �ɽ¼�
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

// �⺻ direct2D api ���
// �Ʒ� ������� �׷��ȿ��� ���Ǵ� ����� �׷��Ƚ� �������� �ű�
// c++ ����� �Լ�, Ŭ���� �� ����
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