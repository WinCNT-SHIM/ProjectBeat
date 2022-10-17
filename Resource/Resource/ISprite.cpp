#include "ISprite.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
ISprite::ISprite()
	: SpriteType(), Index(), Width(), Height(), KeyColor(),
	CenterPosX(), CenterPosY()
{

}

ISprite::ISprite(eSpriteType spriteType, int index, int width, int height, int keyColor,
	int centerPosX, int centerPosY)
	: SpriteType(spriteType), Index(index), Width(width), Height(height), KeyColor(keyColor),
	CenterPosX(centerPosX), CenterPosY(centerPosY)
{

}

ISprite::~ISprite()
{

}