#pragma once
#include "Collider.h"
/// <summary>
/// 원과
/// 선의
/// 충돌
/// 2022.01.08 신성현
/// </summary>
class LineColider : public Collider
{
public:

	LineColider(GameObject* _GameObject);
	~LineColider();

private:
	Vector2D* m_Gradient;
	float m_Range;
public:
	void Init(Vector2D* _Gradient, float _Range);
	virtual bool Check(Collider* other) override;

public:
	virtual void SetName() { m_Name = "LineColider"; }
};

