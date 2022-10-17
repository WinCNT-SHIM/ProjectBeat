#include "stdafx.h"
#include "CircleRender.h"


CircleRender::CircleRender(GameObject* _gameObject) :ShapeRenderer(_gameObject)
{
}

CircleRender::~CircleRender()
{
}

void CircleRender::Update()
{
}

void CircleRender::Render(D2DEngine* engine)
{
	engine->SetTransform(m_GameObject->GetWorldMt());
	engine->DrawCircle(0, 0, (float)_point1, _color, false);
}

void CircleRender::OnStayCollider(GameObject* Other)
{
	_color = 0x00FF0000;
}

void CircleRender::OnExitCollider(GameObject* Other)
{
	_color = 0x00FFFFFF;
}
