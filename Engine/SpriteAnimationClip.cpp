#include "stdafx.h"
#include "SpriteAnimationClip.h"
#include "D2DSprite.h"
#include "ResourceManager.h"

SpriteAnimationClip::SpriteAnimationClip(string _AniClipName, int m_PlayFPS)
{
	this->AniClipName = _AniClipName;
	this->m_PlayFPS = m_PlayFPS;
}

SpriteAnimationClip::~SpriteAnimationClip()
{
    m_SpriteCollection.clear();
}

void SpriteAnimationClip::AddSprite(D2DSprite* _sprite)
{
	m_SpriteCollection.push_back(_sprite);
}

void SpriteAnimationClip::AddSprite(string _spritesheet, string _sprite)
{
	D2DSprite* _d2dsprite = RESOURCE->GetSprite(_spritesheet, _sprite);
	m_SpriteCollection.push_back(_d2dsprite);
}

void SpriteAnimationClip::DrawAniSnap(D2DEngine* _pEngine, Transform* _tr, int _SpriteIndex, float _Ratio /*= 1.f*/, Vector2D _Fill /*= Vector2D(1, 1)*/)
{
	_pEngine->SetTransform(_tr->GetWorldMt());

	if (m_SpriteCollection.empty()) return;
    D2DSprite* _sprite = m_SpriteCollection.at(_SpriteIndex);
	
	_pEngine->DrawSpriteR(
        _sprite->m_SheetIndex,
        (float)_sprite->m_OriX,
        (float)_sprite->m_OriY,
        (float)_sprite->Width,
        (float)_sprite->Height,
        (_sprite->m_OriX - _sprite->CenterPosX) * _Ratio,
        (_sprite->m_OriY - _sprite->CenterPosY) * _Ratio,
        (_sprite->m_OriX - _sprite->CenterPosX + _sprite->Width) * _Ratio,
        (_sprite->m_OriY - _sprite->CenterPosY + _sprite->Height) * _Ratio,
        _Fill.x,
        _Fill.y
    );
}
