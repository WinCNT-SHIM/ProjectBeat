#include "stdafx.h"
#include "AABBCollider.h"



AABBCollider::AABBCollider(GameObject* _GameObject) : Collider(_GameObject)
{
	m_Predrt = { 0,0,0,0 };
}

AABBCollider::~AABBCollider()
{

}

void AABBCollider::Init(Vector2D _rc)
{
	m_rc = _rc;
}

bool AABBCollider::Check(Collider* other)
{
	AABBCollider* cast = dynamic_cast<AABBCollider*>(other);
	if (cast)
	{

		m_Predrt.right = (LONG)abs(m_rc.x * m_tr->GetWorldScale().x);
		m_Predrt.bottom = (LONG)abs(m_rc.y * m_tr->GetWorldScale().y);

		Vector2D _my = m_tr->GetWorldTranslate();
		Vector2D _other = cast->m_tr->GetWorldTranslate();
		if (_my.x + m_Predrt.right <  _other.x - cast->m_Predrt.right ||
			_my.x - m_Predrt.right  > _other.x + cast->m_Predrt.right ||
			_my.y + m_Predrt.bottom < _other.y - cast->m_Predrt.bottom ||
			_my.y - m_Predrt.bottom>  _other.y + cast->m_Predrt.bottom)
			return false;//충돌안함!
		else
			return true; //충돌!
	}
	else
	{
		return false;
	}
}
