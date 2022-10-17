#include "stdafx.h"
#include "LineRender.h"

LineRender::LineRender(GameObject* _gameObject) : ShapeRenderer(_gameObject)
{
}

LineRender::~LineRender()
{
}

void LineRender::Update()
{
}

void LineRender::Render(D2DEngine* engine)
{
	Vector2D pos1 = { (float)_point1 * 0.5f, 0 };
	Vector2D pos2 = { (float)-_point1 * 0.5f, 0 };

	engine->SetTransform(m_GameObject->GetWorldMt());
	engine->DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, _color);
}
