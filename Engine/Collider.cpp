#include "stdafx.h"
#include "Collider.h"

Collider::Collider(GameObject* _GameObject) :Component(_GameObject), isCol(false), ispriorCol(false)
{
	m_GameObject = _GameObject;
	m_tr = _GameObject->m_tr;
	m_pos = &m_tr->GetLocalTranslate();
}

Collider::~Collider()
{
	for (auto iter : m_OtherCollider)
	{
		delete iter.second;
	}
	m_OtherCollider.clear();
}

void Collider::Update()
{
	GameObject* remove = nullptr;
	for (auto iter : m_OtherCollider)
	{

		if (iter.second->m_isCur && !iter.second->m_isPrior)
		{
			m_GameObject->OnEnterCollider(iter.first);
		}
		else if (iter.second->m_isCur && iter.second->m_isPrior)
		{
			m_GameObject->OnStayCollider(iter.first);
		}
		else if (!iter.second->m_isCur && iter.second->m_isPrior)
		{
			m_GameObject->OnExitCollider(iter.first);
			remove = iter.first;
		}
		else
		{
			remove = iter.first;
		}
		iter.second->m_isPrior = iter.second->m_isCur;
		iter.second->m_isCur = false;
	}

	if(remove)
		m_OtherCollider.erase(remove);
}
