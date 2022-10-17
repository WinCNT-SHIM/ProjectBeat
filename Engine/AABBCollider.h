#pragma once
#include "Collider.h"
class AABBCollider : public Collider
{
public:
	AABBCollider(GameObject* _GameObject);
	~AABBCollider();

private:
	RECT m_Predrt;
public:
	Vector2D m_rc;
	void Init(Vector2D _rc);
	virtual bool Check(Collider* other) override;

public:
	virtual void SetName() { m_Name = "AABBCollider"; }
};

