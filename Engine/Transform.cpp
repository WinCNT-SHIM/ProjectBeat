#include "stdafx.h"
#include "Transform.h"

Transform::Transform(GameObject* _GameObject) : Component(_GameObject), m_Pivot(Vector2D(0, 0)),
m_TranslateVector(Vector2D(0, 0)), m_RotateVector(Vector2D(1, 0)), m_ScaleVector(Vector2D(1, 1)), m_Parents(nullptr), m_ReservationWorldTranslateVector(0, 0), m_ReservationLocalTranslateVector(0, 0)
{
	m_WorldRotateVector = m_RotateVector;
	m_WorldScaleVector = m_ScaleVector;
	m_WorldTranslateVector = m_TranslateVector;


}

Transform::~Transform()
{




}
void Transform::Update()
{

}

void Transform::SetLocalTranslateVector(float x, float y)
{
	m_TranslateVector.x = x;
	m_TranslateVector.y = y;
	if (m_GameObject->GetChilds()->empty())
	{
		GetWorldTranslateVector();
	}
	else
	{
		FindLastChild();
	}
}

void Transform::SetLocalTranslateVector(Vector2D _vector)
{
	m_TranslateVector = _vector;

	if (m_GameObject->GetChilds()->empty())
	{
		GetWorldTranslateVector();
	}
	else
	{
		FindLastChild();
	}
}

void Transform::AddLocalTranslateVector(float x, float y)
{
	SetLocalTranslateVector(m_TranslateVector.x + x, m_TranslateVector.y + y);
}

void Transform::SetLocalRotateVector(float x, float y)
{
	m_RotateVector.x = x;
	m_RotateVector.y = y;

	m_RotateVector = m_RotateVector.Nomalize();

	if (m_GameObject->GetChilds()->empty())
	{
		GetWorldRotateVector();
	}
	else
	{
		FindLastChild();
	}

}

void Transform::SetLocalRotateVector(Vector2D _vector)
{
	m_RotateVector = _vector;
	m_RotateVector = m_RotateVector.Nomalize();


	if (m_GameObject->GetChilds()->empty())
	{
		GetWorldRotateVector();
	}
	else
	{
		FindLastChild();
	}
}

void Transform::SetLocalRotateVector(float Degree)
{
	float _Radian = Degree * PI / 180.0f;
	Vector2D _RotateVector;
	_RotateVector.x = cos(_Radian);
	_RotateVector.y = sin(_Radian);

	Transform::SetLocalRotateVector(_RotateVector);
}

void Transform::SetLocalScaleVector(float x, float y)
{
	m_ScaleVector.x = x;
	m_ScaleVector.y = y;
	if (m_GameObject->GetChilds()->empty())
	{
		GetWorldScaleVector();
	}
	else
	{
		FindLastChild();
	}
}

void Transform::SetLocalScaleVector(Vector2D _vector)
{
	m_ScaleVector = _vector;
	if (m_GameObject->GetChilds()->empty())
	{
		GetWorldScaleVector();
	}
	else
	{
		FindLastChild();
	}
}

void Transform::SetWorldTranslateVector(Vector2D _vector)
{
	if (m_GameObject->GetParent() != nullptr)
	{

		D2D1_MATRIX_3X2_F _my = m_WorldMt * MakeTranslateMt(_vector - m_WorldTranslateVector);
		D2D1::Matrix3x2F _pred = RevertToMtrix(_my);

		D2D1::Matrix3x2F _invers = RevertToMtrix(m_GameObject->GetParent()->GetWorldMt());
		_invers.Invert();
		D2D1::Matrix3x2F result = _pred * _invers;
		UpdateTranslate(result);
	}
	else
	{
		SetLocalTranslateVector(_vector);

	}

	if (!m_GameObject->GetChilds()->empty())
	{
		GetWorldTranslateVector();
	}
	else
	{
		FindLastChild();
	}

}

void Transform::SetWorldRotateVector(Vector2D _vector)
{
	if (m_GameObject->GetParent() != nullptr)
	{

		D2D1_MATRIX_3X2_F _my = m_WorldMt * MakeRotateMt((_vector - m_WorldRotateVector).Nomalize());
		D2D1::Matrix3x2F _pred = RevertToMtrix(_my);

		D2D1::Matrix3x2F _invers = RevertToMtrix(m_GameObject->GetParent()->GetWorldMt());
		_invers.Invert();
		D2D1::Matrix3x2F result = _pred * _invers;
		UpdateRotate(result);
	}
	else
	{
		SetLocalRotateVector(_vector);
	}

	if (!m_GameObject->GetChilds()->empty())
	{
		GetWorldRotateVector();
	}
	else
	{
		FindLastChild();
	}
}

void Transform::SetWorldScaleVector(Vector2D _vector)
{
	if (m_GameObject->GetParent() != nullptr)
	{

		D2D1_MATRIX_3X2_F _my = m_WorldMt * MakeScaleMt(_vector);
		D2D1::Matrix3x2F _pred = RevertToMtrix(_my);

		D2D1::Matrix3x2F _invers = RevertToMtrix(m_GameObject->GetParent()->GetWorldMt());
		_invers.Invert();
		D2D1::Matrix3x2F result = _pred * _invers;
		UpdateScale(result);
	}
	else
	{
		SetLocalScaleVector(_vector);

	}

	if (!m_GameObject->GetChilds()->empty())
	{
		GetWorldTranslateVector();
	}
	else
	{
		FindLastChild();
	}
}

void Transform::SetTransform(Vector2D _pos /*= Vector2D(0, 0)*/, Vector2D _Rotate /*= Vector2D(1, 0)*/, Vector2D _Scale /*= Vector2D(1, 1)*/, Vector2D _Pivot /*= Vector2D(0, 0)*/)
{
	m_TranslateVector = _pos;
	m_RotateVector = _Rotate;
	m_ScaleVector = _Scale;
	m_Pivot = _Pivot;

	GetWorldTranslateVector();
	GetWorldRotateVector();
	GetWorldScaleVector();

	if (m_GameObject->GetChilds()->empty())
	{
		GetWorldTranslateVector();
		GetWorldRotateVector();
		GetWorldScaleVector();
	}
	else
	{
		FindLastChild();
	}
}

void Transform::SetTransformParent(Transform* _Parents)
{
	m_Parents = _Parents;

	GetWorldTranslateVector();
	GetWorldRotateVector();
	GetWorldScaleVector();
}



D2D1_MATRIX_3X2_F Transform::MakeTranslateMt(Vector2D m_TranslateVector)
{
	D2D1_MATRIX_3X2_F matrix = { 0 };
	matrix._11 = 1; matrix._12 = 0;
	matrix._21 = 0; matrix._22 = 1;
	matrix._31 = m_TranslateVector.x; matrix._32 = m_TranslateVector.y;

	return matrix;
}

D2D1_MATRIX_3X2_F Transform::MakeRotateMt(Vector2D m_RotateVector)
{
	D2D1_MATRIX_3X2_F matrix = { 0 };

	matrix._11 = m_RotateVector.x; matrix._12 = m_RotateVector.y;
	matrix._21 = -m_RotateVector.y; matrix._22 = m_RotateVector.x;

	matrix._31 = 0; matrix._32 = 0;
	return matrix;
}

D2D1_MATRIX_3X2_F Transform::MakeScaleMt(Vector2D m_ScaleVector)
{
	D2D1_MATRIX_3X2_F matrix = { 0 };
	matrix._11 = m_ScaleVector.x; matrix._12 = 0;
	matrix._21 = 0;				  matrix._22 = m_ScaleVector.y;

	matrix._31 = 0; matrix._32 = 0;
	return matrix;
}

void Transform::SetReservationWorldTranslateVector(Vector2D _vector)
{
	m_ReservationWorldTranslateVector = _vector;
}

void Transform::SetReservationLocalTranslateVector(Vector2D _vector)
{

	m_ReservationLocalTranslateVector = _vector;
}

D2D1_MATRIX_3X2_F Transform::MakeRST()
{
	if (m_Parents)
	{

		m_WorldMt = Transform::MakeTranslateMt(m_Pivot * -1) * Transform::MakeScaleMt(m_ScaleVector) * Transform::MakeRotateMt(m_RotateVector) * Transform::MakeTranslateMt(m_Pivot) * Transform::MakeTranslateMt(m_TranslateVector) * m_Parents->MakeRST();

		Vector2D Result;
		Result.x = m_WorldMt.dx;
		Result.y = m_WorldMt.dy;
		m_WorldTranslateVector = Result;

		Vector2D _WorldRotate;
		_WorldRotate.x = m_WorldMt._11;
		_WorldRotate.y = m_WorldMt._12;
		m_WorldRotateVector = _WorldRotate.Nomalize();

		GetWorldScaleVector();

		return m_WorldMt;
	}
	else
	{
		m_WorldMt = Transform::MakeTranslateMt(m_Pivot * -1) * Transform::MakeScaleMt(m_ScaleVector) * Transform::MakeRotateMt(m_RotateVector) * Transform::MakeTranslateMt(m_Pivot) * Transform::MakeTranslateMt(m_TranslateVector);

		Vector2D Result;
		Result.x = m_WorldMt.dx;
		Result.y = m_WorldMt.dy;
		m_WorldTranslateVector = Result;

		Vector2D _WorldRotate;
		_WorldRotate.x = m_WorldMt._11;
		_WorldRotate.y = m_WorldMt._12;
		m_WorldRotateVector = _WorldRotate.Nomalize();

		GetWorldScaleVector();

		return m_WorldMt;
	}
}


void Transform::UpdateTransform(D2D1::Matrix3x2F _mt)
{
}

void Transform::UpdateTranslate(D2D1::Matrix3x2F _mt)
{
	SetLocalTranslateVector(_mt.dx, _mt.dy);

}

void Transform::UpdateRotate(D2D1::Matrix3x2F _mt)
{
	SetLocalRotateVector(_mt._22, _mt._12);
}

void Transform::UpdateScale(D2D1::Matrix3x2F _mt)
{
	SetLocalScaleVector(_mt._11, _mt._22);
}

D2D1::Matrix3x2F Transform::RevertToMtrix(D2D1_MATRIX_3X2_F _mt)
{
	D2D1::Matrix3x2F _pred;
	_pred.dx = _mt.dx;
	_pred.dy = _mt.dy;
	_pred.m11 = _mt.m11;
	_pred.m12 = _mt.m12;
	_pred.m21 = _mt.m21;
	_pred.m22 = _mt.m22;
	_pred._11 = _mt._11;
	_pred._12 = _mt._12;
	_pred._21 = _mt._21;
	_pred._22 = _mt._22;
	_pred._31 = _mt._31;
	_pred._32 = _mt._32;
	return _pred;
}

Vector2D Transform::GetWorldTranslateVector()
{
	if (m_Parents)
	{
		D2D1_MATRIX_3X2_F pred = MakeRST();
		Vector2D Result;
		Result.x = pred.dx;
		Result.y = pred.dy;
		m_WorldTranslateVector = Result;
		return m_WorldTranslateVector;
	}
	else
	{
		MakeRST();
		m_WorldTranslateVector = m_TranslateVector;
		return m_TranslateVector;
	}
}

Vector2D Transform::GetWorldRotateVector()
{
	if (m_Parents)
	{
		D2D1_MATRIX_3X2_F pred = MakeRST();
		Vector2D _WorldVector;
		_WorldVector.x = pred._11;
		_WorldVector.y = pred._12;
		m_WorldRotateVector = _WorldVector.Nomalize();
		return m_WorldRotateVector;
	}
	else
	{
		m_WorldRotateVector = m_RotateVector;
		MakeRST();
		return m_RotateVector;
	}
}

Vector2D Transform::GetWorldScaleVector()
{
	if (m_Parents)
	{
		D2D1_MATRIX_3X2_F pred = GetWorldScaleMt(m_Parents);
		Vector2D _WorldVector;
		_WorldVector.x = pred._11;
		_WorldVector.y = pred._22;
		m_WorldScaleVector = _WorldVector;
		return m_WorldScaleVector;
	}
	else
	{
		m_WorldScaleVector = m_ScaleVector;
		return m_ScaleVector;
	}
}

D2D1_MATRIX_3X2_F Transform::GetWorldScaleMt(Transform* _tr)
{
	if (_tr->m_Parents)
		return MakeScaleMt(_tr->m_ScaleVector) * GetWorldScaleMt(_tr->m_Parents);
	else
		return MakeScaleMt(_tr->m_ScaleVector);
}

void Transform::FindLastChild()
{
	if (m_GameObject->GetChilds()->empty())
	{
		MakeRST();

	}
	else
	{
		for (auto iter : *m_GameObject->GetChilds())
		{
			iter->m_tr->FindLastChild();
		}
	}
}
