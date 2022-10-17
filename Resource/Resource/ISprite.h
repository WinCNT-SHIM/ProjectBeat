#pragma once
#include <windows.h>

class ISprite abstract
{

public:
	// ������ ����? ����Ƶ� �������� ���
	enum class eSpriteType
	{
		eBWType,	// ���� �������̹��� �����͸� ������ ����. DRSpiteŬ������ ��ӹ޾ƾ� ��
		ePickPos,	// ��ġ, ũ�⸸ ������ ������, �׸� �� �̸� �ε�� ��������Ʈ ��Ʈ���� �Ϻθ� Blit�Ѵ�.
	};

public:
	ISprite();
	ISprite(eSpriteType spriteType, int index, int width, int height, int keyColor,
		int centerPosX, int centerPosY);
	virtual ~ISprite() = 0;

public:
	// ��������Ʈ ���� ���
	eSpriteType SpriteType;

	// ������ Ư�� �ε���(Ű)
	int Index;

	// ��������Ʈ�� ��, ����
	int Width;
	int Height;

	// Ű �÷� (TransparentBlit���� ���)
	int KeyColor;

	// �ִϸ��̼� ����
	int CenterPosX;		// ��Ʈ���� �߽� (ĳ������ �� ��ġ ��)
	int CenterPosY;
};