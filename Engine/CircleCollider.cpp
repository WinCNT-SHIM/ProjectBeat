#include "stdafx.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(GameObject* _GameObject) : Collider(_GameObject)
{

}

CircleCollider::~CircleCollider()
{

}

void CircleCollider::Init(float& _Radius)
{
	Radius = _Radius;
}

bool CircleCollider::Check(Collider* other)
{
	CircleCollider* cast = dynamic_cast<CircleCollider*>(other);
	if (cast)
	{

		m_PredRadius = max((Radius * m_tr->GetWorldScale().x), (Radius * m_tr->GetWorldScale().y));
		Vector2D _pos = m_GameObject->m_tr->GetWorldTranslate();
		Vector2D _Otherpos = cast->m_GameObject->m_tr->GetWorldTranslate();
		float distance = _pos.GetDistance(_Otherpos);
		if (cast->m_PredRadius + m_PredRadius < distance)
			return false;
		else
			return true;
	}
	else
		return false;
}
