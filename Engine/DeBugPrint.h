#pragma once
#include <stdio.h>

static bool DebugMod = false;

void DebugPrint(const char* pFormat, ...);
void DebugRectOnOff();
bool GetDebugMod();
#define DEBUG_PRINT DebugPrint

#ifdef _DEBUG
//���� �ּҿ� ���� ����Ʈ
#define FILE_PRINT() printf("[%s:%d]\n", __FILE__, __LINE__)
//���ϴ� �ؽ�Ʈ ����Ʈ.
#define DEBUG_PRINT  DebugPrint

#else
#define FILE_PRINT() __noop
#define DEBUG_PRINT __noop
#endif