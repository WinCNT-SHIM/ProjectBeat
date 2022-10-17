#include "stdafx.h"
#include "RectRender.h"

RectRender::RectRender(GameObject* _gameObject) : ShapeRenderer(_gameObject)
{
	_color = 0x00FFFFFF;
}

RectRender::~RectRender()
{
}

void RectRender::Update()
{
}


void RectRender::Render(D2DEngine* engine)
{
	//m_GameObject->m_tr
	if (!GetDebugMod()) return;
	
		engine->SetTransform(m_GameObject->GetWorldMt());
		engine->DrawRectangle((float)_point1, (float)_point2, (float)_point3, (float)_point4, _color, false);
	
}

void RectRender::OnStayCollider(GameObject* Other)
{
	_color = 0x00FF0000;
}

void RectRender::OnExitCollider(GameObject* Other)
{
	_color = 0x00FFFFFF;
}

void RectRender::OnEnterCollider(GameObject* Other)
{

}
