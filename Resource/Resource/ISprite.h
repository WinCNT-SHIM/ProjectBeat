#pragma once
#include <windows.h>

class ISprite abstract
{

public:
	// 원본과 연결? 어찌됐든 가져오는 방법
	enum class eSpriteType
	{
		eBWType,	// 실제 래스터이미지 데이터를 가지고 있음. DRSpite클래스를 상속받아야 함
		ePickPos,	// 위치, 크기만 가지고 있으며, 그릴 때 미리 로드된 스프라이트 시트에서 일부를 Blit한다.
	};

public:
	ISprite();
	ISprite(eSpriteType spriteType, int index, int width, int height, int keyColor,
		int centerPosX, int centerPosY);
	virtual ~ISprite() = 0;

public:
	// 스프라이트 구현 방식
	eSpriteType SpriteType;

	// 연결할 특정 인덱스(키)
	int Index;

	// 스프라이트의 폭, 높이
	int Width;
	int Height;

	// 키 컬러 (TransparentBlit같은 경우)
	int KeyColor;

	// 애니메이션 관련
	int CenterPosX;		// 비트맵의 중심 (캐릭터의 발 위치 등)
	int CenterPosY;
};