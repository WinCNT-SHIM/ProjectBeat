#include "stdafx.h"
#include "CBase.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}
Vector2D::Vector2D(float _x, float _y) :x(_x), y(_y)
{
}



Vector2D Vector2D::operator-(const Vector2D& ref)
{
	Vector2D result = { 0,0 };
	result.x = x - ref.x;
	result.y = y - ref.y;

	return result;
}

Vector2D Vector2D::operator-=(const Vector2D& ref)
{
	x = x - ref.x;
	y = y - ref.y;

	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& ref)
{
	Vector2D result = { 0,0 };
	result.x = x + ref.x;
	result.y = y + ref.y;

	return result;
}

Vector2D Vector2D::operator+=(const Vector2D& ref)
{
	x = x + ref.x;
	y = y + ref.y;

	return *this;
}

Vector2D Vector2D::operator*(const float ref)
{
	if (ref == 0)
		return Vector2D(0, 0);

	Vector2D result(x * ref, y * ref);
	return result;
}

Vector2D& Vector2D::operator=(const Vector2D& ref)
{
	x = ref.x;
	y = ref.y;

	return *this;
}
bool Vector2D::operator==(Vector2D ref)
{
	if (x == ref.x && y == ref.y)
		return true;
	else
		return false;
}
bool Vector2D::operator!=(Vector2D ref)
{
	if (x != ref.x || y != ref.y)
		return true;
	else
		return false;
}
float Vector2D::Dot(const Vector2D& ref)
{
	float result = (x * ref.x) + (y * ref.y);
	return result;
}
float Vector2D::GetDistance(const Vector2D& ref)
{
	float result = (float)sqrt(pow((double)ref.x - (double)x, 2) + pow((double)ref.y - (double)y, 2));
	return result;
}

Vector2D Vector2D::Nomalize()
{
	Vector2D Result(0, 0);
	float x2, y2;
	x2 = x * x;
	y2 = y * y;
	float range = (x2 + y2);
	if (range != 0)
	{
		Result.x = x / sqrt(range);
		Result.y = y / sqrt(range);
	}
	return Result;

}

Vector2D Vector2D::SetRotate(float radian)
{
	Vector2D test = *this;
	test.x = this->x * cos(radian) - this->y * sin(radian);
	test.y = this->x * sin(radian) + this->y * cos(radian);

	return test;
}
