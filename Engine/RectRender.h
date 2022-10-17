#pragma once
#include "ShapeRenderer.h"

//�ʱ�ȭ�� �簢�� �� 4��
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

