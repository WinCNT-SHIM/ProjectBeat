#pragma once
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <string>

// �⺻ direct2D api ���
#include <d2d1.h>
// c++ ����� �Լ�, Ŭ���� �� ����
#include <d2d1helper.h>
// text
#include <dwrite.h>
#include <wincodec.h>
// image
#include <wincodec.h>
#include "d2d1effects_2.h"
#include "EngineMacro.h"

#include "ResourceManager.h"

#include <map>
#include <vector>
#include "D2DSpriteSheet.h"
#include "AnimatorController.h"
#include "AudioClip.h"

#include "DataInfo.h"
#include "JsonParse.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Windowscodecs.lib")

using namespace std;