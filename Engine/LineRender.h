#pragma once
#include "ShapeRenderer.h"

//�ʱ�ȭ�� ������ ���� _point1
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

