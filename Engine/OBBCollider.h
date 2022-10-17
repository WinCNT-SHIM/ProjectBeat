#pragma once
#include "Collider.h"

class OBBCollider : public Collider
{
public:
	//������
	OBBCollider(GameObject* _GameObject);
	~OBBCollider();
	//�Ҹ���

private:

	//�簢���� �ʿ��Ѱ�
	float 	m_point1;
	float 	m_point2;
	float 	m_point3;
	float 	m_point4;
	//ȸ���� ����
public:
	Vector2D m_PredGradient;


	void Init(float point1, float point2, float point3, float point4);
	//�浹 üũ
	virtual bool Check(Collider* other) override;

public:
	virtual void SetName() { m_Name = "OBBCollider"; }
};

