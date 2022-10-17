#include "D2DSpriteSheet.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
int D2DSpriteSheet::_spriteSheetCnt = 0;

D2DSpriteSheet::D2DSpriteSheet()
{

	
}

D2DSpriteSheet::D2DSpriteSheet(const D2DSpriteSheet& value)
{
	_sheetName = std::string(value._sheetName);
	_imageFilePath = std::string(value._imageFilePath);

	_spriteSheet.insert(value._spriteSheet.begin(), value._spriteSheet.end());

	_spriteSheetIndex = _spriteSheetCnt++;

}

D2DSpriteSheet::~D2DSpriteSheet()
{
}

void D2DSpriteSheet::AddSprite(std::string name, D2DSprite* sprite)
{
	_spriteSheet.insert({ sprite->m_spriteName, sprite });
}
