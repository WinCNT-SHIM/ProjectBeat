#pragma once
#include <string>
#include "GameObject.h"
class D2DEngine;

using namespace std;

class Component
{
public:
	Component(GameObject* _GameObj); //부모를 게임 오브젝트를 인자로 받고 초기화
	virtual ~Component();

	GameObject* m_GameObject; //부모
	string m_Name;

	bool m_Enable = true;
public:
	
	virtual void Start() { };
	virtual void Update() abstract; // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render(D2DEngine* _pEngine) {}; // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더
	virtual void SetName() abstract;

	//충돌 시작
	virtual void OnEnterCollider(GameObject* Other) {};
	//충돌 중
	virtual void OnStayCollider(GameObject* Other) {};
	//충돌 끝
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

