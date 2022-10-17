#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(GameObject* _GameObject);
	~CircleCollider();
public:
	float Radius;
	float m_PredRadius;
	//CC
	void Init(float& _Radius);
	virtual bool Check(Collider* other) override;
public:
	virtual void SetName() { m_Name = "CircleCollider"; }
};

