#pragma once
#include "Component.h"

/// <summary>
/// 
/// 해보자
/// 물리
/// 2022 - 01 -20신성현
/// </summary>
class Transform;
enum class ColliderType
{
	Circle,
	AABB,
	OBB
};


class Physics : public Component
{
public:
	Physics(GameObject* _GameObject);
	virtual ~Physics();
private:
	Vector2D m_Direction;
	float m_Velocity;
	bool m_isDynamic;
	ColliderType m_ColliderType;
public:
	void init(ColliderType _Type);
	//방향 //속도 //트랜스폼
	void AddForce(Vector2D _Direction, float _Velocity);
	void SetForce(Vector2D _Direction, float _Velocity);
	void SetDynamic(bool _istrue);
	bool GetDynamic() { return m_isDynamic; }


	virtual void Update();
	virtual void OnStayCollider(GameObject* Other) override;
public:
	virtual void SetName() { m_Name = "Physics"; }
};

