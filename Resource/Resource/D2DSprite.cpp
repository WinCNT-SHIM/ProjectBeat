#include "D2DSprite.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
D2DSprite::D2DSprite()
	: ISprite(),
	m_SheetIndex(0), m_OriX(0), m_OriY(0)
{
}

D2DSprite::D2DSprite(int spriteSheetIndex, int oriX, int oriY, int index, int width, int height,
	int keyColor, int centerPosX, int centerPosY)
	: ISprite(eSpriteType::ePickPos, index, width, height, keyColor, centerPosX, centerPosY),
	m_SheetIndex(spriteSheetIndex), m_OriX(oriX), m_OriY(oriY)
{

}

D2DSprite::~D2DSprite()
{
}