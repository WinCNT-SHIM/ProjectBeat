#pragma once
#include "ShapeRenderer.h"

//초기화시 반지름 값 _point1
class CircleRender : public ShapeRenderer
{
public:
	CircleRender(GameObject* _gameObject);
	~CircleRender();
public:
	virtual void Update() override;
	//_Point1 반지름 입력.
	virtual void Render(D2DEngine* engine) override;

	virtual void OnStayCollider(GameObject* Other);
	virtual void OnExitCollider(GameObject* Other);

public:
	virtual void SetName() { m_Name = "CircleRender"; }
};

