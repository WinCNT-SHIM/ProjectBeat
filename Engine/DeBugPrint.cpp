#include "stdafx.h"
#include <stdarg.h>
#include "DeBugPrint.h"

#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

//! ���� !! �����忡 �������� �ʽ��ϴ�.
// printf�� ���� ����.
void	DebugPrint(const char* pFormat, ...)
{
	static char logBuf[8192];
	va_list args;
	va_start(args, pFormat);

	vsprintf_s(logBuf, pFormat, args);
	va_end(args);

	printf(logBuf);
}
void DebugRectOnOff()
{
	DebugMod = !DebugMod;
}

bool GetDebugMod()
{
	return DebugMod;
}
