#pragma once
#include "Component.h"

/// <summary>
/// 
/// �غ���
/// ����
/// 2022 - 01 -20�ż���
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
	//���� //�ӵ� //Ʈ������
	void AddForce(Vector2D _Direction, float _Velocity);
	void SetForce(Vector2D _Direction, float _Velocity);
	void SetDynamic(bool _istrue);
	bool GetDynamic() { return m_isDynamic; }


	virtual void Update();
	virtual void OnStayCollider(GameObject* Other) override;
public:
	virtual void SetName() { m_Name = "Physics"; }
};

