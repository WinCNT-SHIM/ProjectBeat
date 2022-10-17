#include "stdafx.h"
#include "LineColider.h"
#include "CircleCollider.h"
LineColider::LineColider(GameObject* _GameObject) :Collider(_GameObject)
{
}

LineColider::~LineColider()
{
}

void LineColider::Init(Vector2D* _Gradient, float _Range)
{
	m_Gradient = _Gradient;
	m_Range = _Range;
}

bool LineColider::Check(Collider* other)
{
	CircleCollider* _cast = dynamic_cast<CircleCollider*>(other);
	if (_cast)
	{
		Vector2D Q = m_tr->GetWorldTranslate(); //���� ��ǥ
		Vector2D V = *m_Gradient; //����
		Vector2D O = _cast->m_tr->GetWorldTranslate(); //���� �߽�
		float T = m_Range * m_tr->GetWorldScale().x; //����



		float D = ((V.Dot(Q) - V.Dot(O)) * (V.Dot(Q) - V.Dot(O)))
			- V.Dot(V)
			* (Q.Dot(Q) + O.Dot(O) - (float)pow(_cast->Radius, 2) - O.Dot(Q) * 2.0f);

		float dis = O.GetDistance(Q);
		if (D < 0)
			return false;

		if (D >= 0)
		{

			float t = ((-((Q - O).Dot(V))) + sqrt(D)) / (V.Dot(V));
			float t1 = ((-((Q - O).Dot(V))) - sqrt(D)) / (V.Dot(V));

			if (t <= T && t >= -T)
				return true;

			if (t1 <= T && t1 >= -T)
				return true;


		}
	}
	return false;
}
/*

(x-x1)^2(y-y1)^2 = r^2

*
ax+by+c = 0;
�� ���� �־����� ��..
�ϴ�

(x,y)  (x1,y1)


m(����) : (y1-y)/(x1-x);
m : - a / b

a = -(y1-y)
b = x1-x
c = -(y-(����*x)* b)

d = |ax(���� ����) + by(���� ����) + c| /  sqrt(a^2 + b^2)

������ ���� �Ÿ�..

(x-x1)^2 + (y-y1)^2 = r^2

x^2(1+m^2) + 2x(mc -x1-ym) + x1^2+y^2-2yc+c^2-r^2 = 0

A = (1+m)
B = 2(mc-x1-yn)
C = x1^2+ y^2 -2yc +c^2 - r^2

D = B^2 - 4AC;




		float x, y, x1, y1, m;
		float a, b, c, d;
		x = pos->x;
		y = pos->y;
		x1 = pos->x + m_EndPos.x;
		y1 = pos->y + m_EndPos.y;

		if (_cast->pos->x + _cast->Radius > x &&
			_cast->pos->x - _cast->Radius < x1 &&
			_cast->pos->y + _cast->Radius > y &&
			_cast->pos->y - _cast->Radius < y1
			)
		{
			if ((y - y1) != 0 && (x - x1) != 0)
			{
				m = (y1 - y) / (x1 - x);

				a = -(y1 - y);
				b = x1 - x;
				c = -((y1 - (m * x1)) * b);

				d = abs((a * _cast->pos->x) + (b * _cast->pos->y) + (c)) / sqrt(pow(a, 2) + pow(b, 2));

				if (d <= _cast->Radius)
					return true;

				/*		c = (y * x1 - x * y1) / (x1 - x);
						float A, B, C, D;
						A = (1 + m * m);
						B = (m * c - _cast->pos->x - _cast->pos->y * m);
						C = pow(_cast->pos->x, 2) + pow(_cast->pos->y, 2) - 2 * _cast->pos->y * c + pow(c, 2) - pow(_cast->Radius, 2);

						D = pow(B, 2) - A * C;
						if (D >= 0)
							return true;

			}
			else if ((y - y1) == 0)
			{

			if (_cast->pos->y + _cast->Radius > y && _cast->pos->y - _cast->Radius < y)
				return true;
			}
			else if ((x1 - x) == 0)
			{

			if (_cast->pos->x + _cast->Radius > x && _cast->pos->x - _cast->Radius < x)
				return true;
			}
			else
			{

			}
		}


*/