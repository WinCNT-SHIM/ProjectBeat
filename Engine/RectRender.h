#pragma once
#include "ShapeRenderer.h"

//초기화시 사각형 점 4개
class RectRender : public ShapeRenderer
{
public:
	RectRender(GameObject* _gameObject);
	~RectRender();
public:
	virtual void Update() override;
	virtual void Render(D2DEngine* engine) override;

	virtual void OnStayCollider(GameObject* Other) override;
	virtual void OnExitCollider(GameObject* Other) override;
	virtual void OnEnterCollider(GameObject* Other) override;

public:
	virtual void SetName() { m_Name = "RectRender"; }
};

