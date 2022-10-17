#pragma once
#include "Collider.h"

class OBBCollider : public Collider
{
public:
	//생성자
	OBBCollider(GameObject* _GameObject);
	~OBBCollider();
	//소멸자

private:

	//사각형에 필요한것
	float 	m_point1;
	float 	m_point2;
	float 	m_point3;
	float 	m_point4;
	//회전을 위한
public:
	Vector2D m_PredGradient;


	void Init(float point1, float point2, float point3, float point4);
	//충돌 체크
	virtual bool Check(Collider* other) override;

public:
	virtual void SetName() { m_Name = "OBBCollider"; }
};

