#include "stdafx.h"
#include "Physics.h"
#include "OBBCollider.h"
#include "CircleCollider.h"
#include "AABBCollider.h"

Physics::Physics(GameObject* _GameObject) :Component(_GameObject), m_Direction(0, 0)
{
	m_Velocity = 0;
	m_isDynamic = false;
	m_ColliderType = ColliderType::Circle;
}

Physics::~Physics()
{

}

void Physics::init(ColliderType _Type)
{
	m_ColliderType = _Type;
}

//힘을 더하는 식으로
//스칼라와 벡터
void Physics::AddForce(Vector2D _Direction, float _Velocity)
{
	if (m_isDynamic)
	{
		_Velocity = _Velocity * m_GameObject->m_Speed;
		if (_Velocity < 0.000001)
			return;

		m_Direction = (m_Direction * m_Velocity + _Direction.Nomalize() * _Velocity);

		m_Velocity = (float)sqrt(pow(m_Direction.x, 2) + pow(m_Direction.y, 2));
		m_Direction = Vector2D(m_Direction.x / m_Velocity, m_Direction.y / m_Velocity);

		if (m_Velocity > 200)
			m_Velocity = 200;
	}
}

void Physics::SetForce(Vector2D _Direction, float _Velocity)
{
	m_Direction = _Direction.Nomalize();
	m_Velocity = _Velocity;
}

void Physics::SetDynamic(bool _istrue)
{
	m_isDynamic = _istrue;
}

void Physics::Update()
{
	if (m_isDynamic)
	{
		AddForce(Vector2D(0, 1), 2 * m_GameObject->m_Speed);
		if (m_Velocity > 0.2)
		{
			m_GameObject->SetLocalTranslateVector(m_GameObject->GetLocalTranslate() + m_Direction * m_Velocity);
			m_Velocity -= 0.3f * m_GameObject->m_Speed;
		}
		else
		{
			m_Velocity = 0;
		}
	}
}

void Physics::OnStayCollider(GameObject* Other)
{
	if (m_isDynamic)
	{
		if (!Other->m_Pyhsics) return;

		switch (m_ColliderType)
		{
		case ColliderType::Circle:
		{
			CircleCollider* _cast = dynamic_cast<CircleCollider*>(Other->collider);
			if (_cast)
			{
				AddForce(
					m_GameObject->GetWorldTranslate() - Other->GetWorldTranslate(),
					1);

				Other->m_Pyhsics->AddForce(Other->GetWorldTranslate() - m_GameObject->GetWorldTranslate(),
					1);
			}
			break;
		}

		case ColliderType::AABB:
		{
			AABBCollider* _cast = dynamic_cast<AABBCollider*>(Other->collider);
			if (_cast)
			{
				Vector2D _Rc = dynamic_cast<AABBCollider*>(m_GameObject->collider)->m_rc;


				float force = 0;
				Vector2D _pred = m_GameObject->GetWorldTranslate();
				Vector2D _Other = _cast->m_GameObject->GetWorldTranslate();


				float forcex = (_Rc.x + _cast->m_rc.x) - abs(_pred.x - _Other.x);
				float forcey = (_Rc.y + _cast->m_rc.y) - abs(_pred.y - _Other.y);
				if (forcex < forcey)
				{


					_pred = Vector2D(_pred.x - _Other.x, 0);
					if (_pred.x > 0)
					{
						//버그를 막기 위해... 이러면 안되지만..
						if ((_Other.x + (_Rc.x + _cast->m_rc.x) > 99) && (_Other.x + (_Rc.x + _cast->m_rc.x) < 1821))
							m_GameObject->m_tr->SetWorldTranslateVector(Vector2D((_Other.x + (_Rc.x + _cast->m_rc.x)), m_GameObject->GetWorldTranslate().y));

					}
					else
					{
						if ((_Other.x - (_Rc.x + _cast->m_rc.x) > 99) && (_Other.x - (_Rc.x + _cast->m_rc.x) < 1821))
							m_GameObject->m_tr->SetWorldTranslateVector(Vector2D((_Other.x - (_Rc.x + _cast->m_rc.x)), m_GameObject->GetWorldTranslate().y));

					}

					/*_pred = Vector2D(_pred.x - _Other.x, 0);
					AddForce(_pred, forcex / 2);*/
				}
				else
				{
					_pred = Vector2D(0, _pred.y - _Other.y);
					if (_pred.y < 0)
					{
						m_GameObject->m_tr->SetWorldTranslateVector(Vector2D(m_GameObject->GetWorldTranslate().x, (_Other.y - (_Rc.y + _cast->m_rc.y))));
						if (m_Direction.y > 0)
							SetForce(Vector2D(m_Direction.x, 0), m_Velocity / 4);

					}
					else
					{
						m_GameObject->m_tr->SetWorldTranslateVector(Vector2D(m_GameObject->GetWorldTranslate().x, (_Other.y + (_Rc.y + _cast->m_rc.y))));
						if (m_Direction.y < 0)
							SetForce(Vector2D(m_Direction.x, 0), m_Velocity / 4);
					}
					AddForce(Vector2D(0, -1), 2 * m_GameObject->m_Speed);
				}
			}
			break;
		}

		case ColliderType::OBB:
		{
			//Obb물리은 나중에 하자..!
			//OBBCollider* _cast = dynamic_cast<OBBCollider*>(Other->collider);
			//if (_cast)
			//{
			//	AddForce(
			//		m_GameObject->GetWorldTranslate() - Other->GetWorldTranslate(),
			//		1);

			//	Other->m_Pyhsics->AddForce(Other->GetWorldTranslate() - m_GameObject->GetWorldTranslate(),
			//		1);
			//}
			break;
		}

		default:
			break;
		}

	}
}
