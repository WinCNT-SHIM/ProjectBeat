#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(Vector2D _pos, Vector2D _Rotate, Vector2D _Scale, Vector2D _Pivot, string _tag)
	: m_teg(_tag), m_Parent(nullptr), m_Name("Empty")
{

	m_tr = AddComponent<Transform>();
	m_tr->SetTransform(_pos, _Rotate, _Scale, _Pivot);
}

GameObject::~GameObject()
{
	for (auto iter : m_Components)
	{
		delete iter;
	}
	m_Components.clear();
}

void GameObject::PhysicsUpdate()
{
	for (auto iter : m_Components)
	{
		if (iter->GetName() == "Physics")
		{
			if (iter->m_Enable)
				iter->Update();
		}
	}
}

void GameObject::Update()
{
	for (auto iter : m_Components)
	{
		if (iter->GetName() == "Physics")
			continue;
		if (iter->m_Enable)
			iter->Update();
	}
}

void GameObject::OnEnterCollider(GameObject* Other)
{
	for (auto iter : m_Components)
	{
		if (iter->m_Enable)
			iter->OnEnterCollider(Other);
	}
}

void GameObject::OnStayCollider(GameObject* Other)
{
	if (collider->Check(Other->collider))
	{
		for (auto iter : m_Components)
		{
			if (iter->m_Enable)
				iter->OnStayCollider(Other);
		}
	}
}

void GameObject::OnExitCollider(GameObject* Other)
{
	for (auto iter : m_Components)
	{
		if (iter->m_Enable)
			iter->OnExitCollider(Other);
	}
}

void GameObject::AddChild(GameObject* _child)
{
	m_Childs.push_back(_child);
}

void GameObject::SetParent(GameObject* _Parent)
{
	_Parent->AddChild(this);
	m_Parent = _Parent;
	m_tr->SetTransformParent(_Parent->m_tr);
}

GameObject* GameObject::GetTopParent()
{
	if (m_Parent)
	{
		return m_Parent->GetTopParent();
	}
	return this;
}

void GameObject::SetChildsTeg(string _teg)
{
	m_teg = _teg;
	for (auto iter : *GetChilds())
	{
		iter->m_teg = _teg;
		if (!iter->GetChilds()->empty())
			iter->SetChildsTeg(_teg);
	}
}

void GameObject::SetLocalTranslateVector(float x, float y)
{
	m_tr->SetLocalTranslateVector(x, y);
}

void GameObject::SetLocalTranslateVector(Vector2D _vector)
{
	m_tr->SetLocalTranslateVector(_vector);
}

void GameObject::SetLocalRotateVector(float x, float y)
{
	m_tr->SetLocalRotateVector(x, y);
}

void GameObject::SetLocalRotateVector(Vector2D _vector)
{
	m_tr->SetLocalRotateVector(_vector);
}

void GameObject::SetLocalRotateVector(float degree)
{
	m_tr->SetLocalRotateVector(degree);
}

void GameObject::SetLocalScaleVector(float x, float y)
{
	m_tr->SetLocalScaleVector(x, y);
}

void GameObject::SetLocalScaleVector(Vector2D _vector)
{
	m_tr->SetLocalScaleVector(_vector);
}

Vector2D GameObject::GetLocalTranslate()
{
	return m_tr->GetLocalTranslate();

}

Vector2D GameObject::GetLocalRotate()
{
	return m_tr->GetLocalRotate();
}

Vector2D GameObject::GetLocalScale()
{
	return m_tr->GetLocalScale();
}

Vector2D GameObject::GetWorldTranslate()
{
	return m_tr->GetWorldTranslate();
}

Vector2D GameObject::GetWorldRotate()
{
	return m_tr->GetWorldRotate();
}

Vector2D GameObject::GetWorldScale()
{
	return m_tr->GetWorldScale();
}

D2D1_MATRIX_3X2_F GameObject::GetWorldMt()
{
	return m_tr->GetWorldMt();

}



Component* GameObject::GetComponent(string _string)
{
	Component* tempComponent = nullptr;
	for (auto iter : m_Components)
	{
		if (iter->GetName() == _string)
			tempComponent = iter;
		if (tempComponent != nullptr)
		{
			return tempComponent;
		}
	}
	return nullptr;
	return nullptr;
}

