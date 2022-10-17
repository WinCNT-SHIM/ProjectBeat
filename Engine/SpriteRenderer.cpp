#pragma once
#include "stdafx.h"
#include "SpriteRenderer.h"
#include "D2DSprite.h"
#include "ResourceManager.h"
#include "OBBCollider.h"
#include "RectRender.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject) : Renderer(gameObject), _color(0xFFFFFF), m_Ratio(0.2f), m_isActive(true)
{
	m_Fill = { 1, 1 };
}

SpriteRenderer::~SpriteRenderer()
{
}


void SpriteRenderer::Init(D2DSprite* sprite, float _ratio)
{
	_sprite = sprite;
	m_Ratio = _ratio;
	leftTop.x = (_sprite->m_OriX - _sprite->CenterPosX) * m_Ratio;
	leftTop.y = (_sprite->m_OriY - _sprite->CenterPosY) * m_Ratio;
	rightBot.x = (_sprite->m_OriX - _sprite->CenterPosX + _sprite->Width) * m_Ratio;
	rightBot.y = (_sprite->m_OriY - _sprite->CenterPosY + _sprite->Height) * m_Ratio;

	/// 애니메이션을 초기화 할 때, 애니메이션의 스프라이트 정보값이 필요하긴 해서 이렇게 했는데.. 이게 맞을까
	OBBCollider* collider = GetComponent<OBBCollider>();
	if (collider)
	{
		float _Width = (rightBot.x - leftTop.x) / 2;
		float _Height = (rightBot.y - leftTop.y) / 2;
		dynamic_cast<OBBCollider*>(collider)->Init(leftTop.x, leftTop.y, rightBot.x, rightBot.y);
		RectRender* rectreder = GetComponent<RectRender>();
		if (rectreder)
			rectreder->Init(leftTop.x, leftTop.y, rightBot.x, rightBot.y);
	}

}


void SpriteRenderer::Init(string _Sheetname, string _SpriteName, float _ratio)
{
	SetSprite(_Sheetname, _SpriteName, _ratio);
}


void SpriteRenderer::SetSprite(std::string sheetName, std::string spriteName, float _ratio)
{
	_sprite = RESOURCE->GetSprite(sheetName, spriteName);

	m_Ratio = _ratio;
	leftTop.x = (_sprite->m_OriX - _sprite->CenterPosX) * m_Ratio;
	leftTop.y = (_sprite->m_OriY - _sprite->CenterPosY) * m_Ratio;
	rightBot.x = (_sprite->m_OriX - _sprite->CenterPosX + _sprite->Width) * m_Ratio;
	rightBot.y = (_sprite->m_OriY - _sprite->CenterPosY + _sprite->Height) * m_Ratio;

	/// 애니메이션을 초기화 할 때, 애니메이션의 스프라이트 정보값이 필요하긴 해서 이렇게 했는데.. 이게 맞을까
	OBBCollider* collider = GetComponent<OBBCollider>();
	if (collider)
	{
		dynamic_cast<OBBCollider*>(collider)->Init(leftTop.x, leftTop.y, rightBot.x, rightBot.y);
		RectRender* rectreder = GetComponent<RectRender>();
		if (rectreder)
			rectreder->Init(leftTop.x, leftTop.y, rightBot.x, rightBot.y);
	}
}

void SpriteRenderer::SetDrawMode(DrawMode mode)
{
	_drawMode = mode;
}

void SpriteRenderer::Update()
{
}

void SpriteRenderer::Render(D2DEngine* _pEngine)
{
	if (!_sprite || !m_isActive ) return;

	_pEngine->SetTransform(m_GameObject->GetWorldMt());
	//_pEngine->SetTransform(m_GameObject->m_tr->MakeRST(m_GameObject->m_tr));
	//_pEngine->SetTransform(m_GameObject->MakeRST());
	_pEngine->SetBrushColor(_color);

	switch (_drawMode)
	{
	case DrawMode::Simple:
		_pEngine->DrawSpriteR(_sprite->m_SheetIndex, (float)_sprite->m_OriX, (float)_sprite->m_OriY, (float)_sprite->Width, (float)_sprite->Height, leftTop.x, leftTop.y, rightBot.x, rightBot.y, 1.f, 1.f, _alpha);
		break;
	case DrawMode::Fill:
		_pEngine->DrawSpriteR(_sprite->m_SheetIndex, (float)_sprite->m_OriX, (float)_sprite->m_OriY, (float)_sprite->Width, (float)_sprite->Height, leftTop.x, leftTop.y, rightBot.x, rightBot.y, m_Fill.x, m_Fill.y, _alpha);
		break;
	default:
		_pEngine->DrawSpriteR(_sprite->m_SheetIndex, (float)_sprite->m_OriX, (float)_sprite->m_OriY, (float)_sprite->Width, (float)_sprite->Height, leftTop.x, leftTop.y, rightBot.x, rightBot.y, 1.f, 1.f, _alpha);
		break;
	}

}

void SpriteRenderer::DrawGizmo()
{

}

void SpriteRenderer::SetFill(float _FillX, float _FillY)
{
	/// <summary>
	/// 비어있기에 추가함
	/// 2022.02.15 심승수
	/// </summary>
	// Fill의 값이 0~1이 되도록 조정
	if (_FillX < 0) _FillX = 0;
	if (_FillX > 1) _FillX = 1;
	if (_FillY < 0) _FillY = 0;
	if (_FillY > 1) _FillY = 1;

	m_Fill = Vector2D(_FillX, _FillY);
}
