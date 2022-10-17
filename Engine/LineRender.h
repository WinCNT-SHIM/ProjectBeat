#pragma once
#include "ShapeRenderer.h"

//초기화시 선분의 길이 _point1
class LineRender : public ShapeRenderer
{
public:
	LineRender(GameObject* _gameObject);
	~LineRender();
public:
	virtual void Update() override;
	virtual void Render(D2DEngine* engine) override;


public:
	virtual void SetName() { m_Name = "LineRender"; }
};

