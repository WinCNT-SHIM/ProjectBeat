#pragma once
//#include "CTime.h"
#include <string>
#include <vector>
#include <Windows.h>
#include "CBase.h"
#include "DeBugPrint.h"

//이러면 안되지만 일단..
#include <d2d1.h>


using namespace std;

class D2DEngine;
class Transform;
class Component;
class Collider;
class Physics;

class GameObject
{

public:
	GameObject(Vector2D _pos = Vector2D(0, 0), Vector2D _Rotate = Vector2D(1, 0),
		Vector2D _Scale = Vector2D(1, 1), Vector2D _Pivot = Vector2D(0, 0), string _tag = " ");

	virtual ~GameObject();

private:
	//부모!
	GameObject* m_Parent;
	//내 이름!
	string m_Name;
	vector<GameObject*>m_Childs;
	int m_Layer = 0;
public:
	// 이동 속도 뿐만 아닌 전체적인 속도.
	float m_Speed = 1;
	// 게임 오브젝트 활성화 상태
	bool m_ActiveSelf = true;

	//충돌체크 용도
	string m_teg;
	Transform* m_tr = nullptr;
	Collider* collider = nullptr;
	Physics* m_Pyhsics = nullptr;
	// Physics 업데이트.
	void PhysicsUpdate();
	
	//업데이트
	virtual void Update();
	//충돌 시작
	void OnEnterCollider(GameObject* Other);
	//충돌 중
	void OnStayCollider(GameObject* Other);
	//충돌 끝
	void OnExitCollider(GameObject* Other);

	virtual void Start() {};
public:
	void AddChild(GameObject* _child);
	GameObject* GetChild(int idx)
	{
		if (m_Childs.size() > (unsigned int)idx)
		{
			return m_Childs[idx];
		}
		return nullptr;
	};

	vector<GameObject*>* GetChilds() { return &m_Childs; }
	void SetParent(GameObject* _Parent);
	GameObject* GetParent() { return m_Parent; }
	GameObject* GetTopParent();

	void SetName(string _Name) { m_Name = _Name; }
	string GetName() { return m_Name; }

	int GetLayer() { return m_Layer; }
	void SetLayer(int _num) { m_Layer = _num; }

	void SetActive(bool active) { 
	
		m_ActiveSelf = active; 
		for (auto child : m_Childs)
		{
			child->SetActive(active);
		}
	}

	void SetChildsTeg(string _teg);

	void SetLocalTranslateVector(float x, float y);
	void SetLocalTranslateVector(Vector2D _vector);

	void SetLocalRotateVector(float x, float y);
	void SetLocalRotateVector(Vector2D _vector);
	void SetLocalRotateVector(float degree);

	void SetLocalScaleVector(float x, float y);
	void SetLocalScaleVector(Vector2D _vector);

	//로컬좌표 받아오기
	Vector2D GetLocalTranslate(); //{ return m_tr->GetLocalTranslate(); }
	Vector2D GetLocalRotate(); //{ return m_tr->GetLocalRotate(); }
	Vector2D GetLocalScale();// { return m_tr->GetLocalScale(); }

	//월드좌표 받아오기
	Vector2D GetWorldTranslate(); //{ return m_tr->GetWorldTranslate(); }
	Vector2D GetWorldRotate(); //{ return m_tr->GetWorldRotate(); }
	Vector2D GetWorldScale(); //{ return m_tr->GetWorldScale(); }

	D2D1_MATRIX_3X2_F GetWorldMt(); //{ return m_tr->GetWorldMt(); }


public:
	//컴포넌트 기반 변수 및 함수들
	std::vector<Component*> m_Components;

	template<class TComponent>
	TComponent* AddComponent();

	template<class TComponent>
	TComponent* GetComponent();

	Component* GetComponent(string _string);


	template<class TComponent>
	void DeleteComponent();
};

template<class TComponent>
TComponent* GameObject::AddComponent()
{
	TComponent* tempComponent = new TComponent(this);
	tempComponent->SetName();
	m_Components.emplace_back(tempComponent);

	return tempComponent;
}

template<class TComponent>
TComponent* GameObject::GetComponent()
{
	for (auto iter : m_Components)
	{
		TComponent* tempComponent = dynamic_cast<TComponent*>(iter);

		if (tempComponent != nullptr)
		{
			return tempComponent;
		}
	}

	return nullptr;
}


template<class TComponent>
void GameObject::DeleteComponent()
{
	for (auto iter : m_Components)
	{
		TComponent* tempComponent = dynamic_cast<TComponent*>(iter);

		if (tempComponent != nullptr)
		{
			delete iter;
			iter = nullptr;
			return;
		}
	}
	return;
}

