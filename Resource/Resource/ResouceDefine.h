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

// 기본 direct2D api 헤더
#include <d2d1.h>
// c++ 도우미 함수, 클래스 및 구조
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