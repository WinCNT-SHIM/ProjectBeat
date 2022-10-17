#pragma once
#include <string>
#include "GameObject.h"
class D2DEngine;

using namespace std;

class Component
{
public:
	Component(GameObject* _GameObj); //�θ� ���� ������Ʈ�� ���ڷ� �ް� �ʱ�ȭ
	virtual ~Component();

	GameObject* m_GameObject; //�θ�
	string m_Name;

	bool m_Enable = true;
public:
	
	virtual void Start() { };
	virtual void Update() abstract; // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render(D2DEngine* _pEngine) {}; // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����
	virtual void SetName() abstract;

	//�浹 ����
	virtual void OnEnterCollider(GameObject* Other) {};
	//�浹 ��
	virtual void OnStayCollider(GameObject* Other) {};
	//�浹 ��
	virtual void OnExitCollider(GameObject* Other) {};
	
	
	string GetName() { return m_Name; }



public:
	template<class TComponent>
	TComponent* AddComponent();

	template<class TComponent>
	TComponent* GetComponent();
};
template<class TComponent>
TComponent* Component::AddComponent()
{
	TComponent* tempComponent = new TComponent(this);
	tempComponent->SetName();
	m_GameObject->m_Components.emplace_back(tempComponent);

	return tempComponent;
}

template<class TComponent>
TComponent* Component::GetComponent()
{
	for (auto iter : m_GameObject->m_Components)
	{
		TComponent* tempComponent = dynamic_cast<TComponent*>(iter);

		if (tempComponent != nullptr)
		{
			return tempComponent;
		}
	}

	return nullptr;
}

