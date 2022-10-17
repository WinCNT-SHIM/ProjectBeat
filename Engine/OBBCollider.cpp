#include "stdafx.h"
#include "OBBCollider.h"


OBBCollider::OBBCollider(GameObject* _GameObject) :Collider(_GameObject)
{
	m_point1 = 0;
	m_point2 = 0;
	m_point3 = 0;
	m_point4 = 0;
}

OBBCollider::~OBBCollider()
{

}

void OBBCollider::Init(float point1, float point2, float point3, float point4)
{
	m_point1 = point1;//leftop //left
	m_point2 = point2;//leftop //top
	m_point3 = point3;//rightbottom //right 
	m_point4 = point4;//rightbottom //bottom
}

bool OBBCollider::Check(Collider* other)
{
	OBBCollider* _cast = dynamic_cast<OBBCollider*>(other);

	if (_cast)
	{
		m_GameObject->GetWorldMt();

		//m_Predrt.right = m_rt->right * m_tr->m_ScaleVector.x;
		//m_Predrt.bottom = m_rt->bottom * m_tr->m_ScaleVector.y;
		m_PredGradient = m_tr->GetWorldRotate();
		m_PredGradient = m_PredGradient.Nomalize();
		//m_Predrt.x = (m_pWidth * m_tr->GetWorldScale().x);
		//m_Predrt.y = (m_pHeight * m_tr->GetWorldScale().y);
		Vector2D p1(m_point1, m_point2);
		Vector2D p2(m_point3, m_point2);
		Vector2D p3(m_point3, m_point4);
		Vector2D p4(m_point1, m_point4);
		Vector2D pred(1, 0);

		D2D1_MATRIX_3X2_F _mt1 = Transform::MakeTranslateMt(p1) * m_GameObject->GetWorldMt();
		D2D1_MATRIX_3X2_F _mt2 = Transform::MakeTranslateMt(p2) * m_GameObject->GetWorldMt();
		D2D1_MATRIX_3X2_F _mt3 = Transform::MakeTranslateMt(p3) * m_GameObject->GetWorldMt();
		D2D1_MATRIX_3X2_F _mt4 = Transform::MakeTranslateMt(p4) * m_GameObject->GetWorldMt();

		p1 = Vector2D(_mt1.dx, _mt1.dy);
		p2 = Vector2D(_mt2.dx, _mt2.dy);
		p3 = Vector2D(_mt3.dx, _mt3.dy);
		p4 = Vector2D(_mt4.dx, _mt4.dy);


		Vector2D __Pred = (p2 - p1);
		float _1 = (__Pred).Dot(p1);
		float _2 = (__Pred).Dot(p2);
		float _3;
		float _4;


		float _Min1;
		float _Max1;

		_Min1 = min(_1, _2);
		_Max1 = max(_1, _2);

		Vector2D p11(_cast->m_point1, _cast->m_point2);
		Vector2D p22(_cast->m_point3, _cast->m_point2);
		Vector2D p33(_cast->m_point3, _cast->m_point4);
		Vector2D p44(_cast->m_point1, _cast->m_point4);

		D2D1_MATRIX_3X2_F _mt11 = Transform::MakeTranslateMt(p11) * _cast->m_GameObject->GetWorldMt();
		D2D1_MATRIX_3X2_F _mt22 = Transform::MakeTranslateMt(p22) * _cast->m_GameObject->GetWorldMt();
		D2D1_MATRIX_3X2_F _mt33 = Transform::MakeTranslateMt(p33) * _cast->m_GameObject->GetWorldMt();
		D2D1_MATRIX_3X2_F _mt44 = Transform::MakeTranslateMt(p44) * _cast->m_GameObject->GetWorldMt();

		p11 = Vector2D(_mt11.dx, _mt11.dy);
		p22 = Vector2D(_mt22.dx, _mt22.dy);
		p33 = Vector2D(_mt33.dx, _mt33.dy);
		p44 = Vector2D(_mt44.dx, _mt44.dy);

		_1 = (__Pred).Dot(p11);
		_2 = (__Pred).Dot(p22);
		_3 = (__Pred).Dot(p33);
		_4 = (__Pred).Dot(p44);


		float _Min2;
		float _Max2;



		_Min2 = min(_1, _2);
		_Min2 = min(_Min2, _3);
		_Min2 = min(_Min2, _4);
		_Max2 = max(_1, _2);
		_Max2 = max(_Max2, _3);
		_Max2 = max(_Max2, _4);

		__Pred = (p1 - p4);
		__Pred = __Pred.Nomalize();
		float _Min3;
		float _Max3;

		_1 = (__Pred).Dot(p1);
		_4 = (__Pred).Dot(p4);

		_Min3 = min(_1, _4);
		_Max3 = max(_1, _4);



		float _Min4;
		float _Max4;

		_1 = (__Pred).Dot(p11);
		_2 = (__Pred).Dot(p22);
		_3 = (__Pred).Dot(p33);
		_4 = (__Pred).Dot(p44);

		_Min4 = min(_1, _2);
		_Min4 = min(_Min4, _3);
		_Min4 = min(_Min4, _4);
		_Max4 = max(_1, _2);
		_Max4 = max(_Max4, _3);
		_Max4 = max(_Max4, _4);



		if (_Max1 < _Min2 || _Min1 > _Max2 ||
			_Max3 < _Min4 || _Min3 > _Max4)
			return false;
		else
		{

			Vector2D __Pred = (p22 - p11);

			_1 = (__Pred).Dot(p1);
			_2 = (__Pred).Dot(p2);
			_3 = (__Pred).Dot(p3);
			_4 = (__Pred).Dot(p4);

			_Min1 = min(_1, _2);
			_Min1 = min(_Min1, _3);
			_Min1 = min(_Min1, _4);
			_Max1 = max(_1, _2);
			_Max1 = max(_Max1, _3);
			_Max1 = max(_Max1, _4);


			_1 = (__Pred).Dot(p11);
			_2 = (__Pred).Dot(p22);


			_Min2 = min(_1, _2);
			_Max2 = max(_1, _2);

			__Pred = (p11 - p44);
			__Pred = __Pred.Nomalize();

			_1 = (__Pred).Dot(p1);
			_2 = (__Pred).Dot(p2);
			_3 = (__Pred).Dot(p3);
			_4 = (__Pred).Dot(p4);

			_Min3 = min(_1, _2);
			_Min3 = min(_Min3, _3);
			_Min3 = min(_Min3, _4);
			_Max3 = max(_1, _2);
			_Max3 = max(_Max3, _3);
			_Max3 = max(_Max3, _4);

			_1 = (__Pred).Dot(p11);
			_4 = (__Pred).Dot(p44);

			_Min4 = min(_1, _4);
			_Max4 = max(_1, _4);


			if (_Max1 < _Min2 || _Min1 > _Max2 ||
				_Max3 < _Min4 || _Min3 > _Max4)
				return false;
			else
				return true;
		}
	}
	return false;
}
