#pragma once
// 미리 컴파일된 헤더 파일로 이식
//#include <math.h>
//#include <windows.h>
//#include <dwrite.h>
//#include <d2d1.h>

#define PI 3.14159265358979f

struct Vector2D
{
	float x;
	float y;

	Vector2D();
	Vector2D(float _x, float _y);
	Vector2D operator-(const Vector2D& ref);
	Vector2D operator-=(const Vector2D& ref);

	Vector2D operator+(const Vector2D& ref);
	Vector2D operator+=(const Vector2D& ref);

	Vector2D& operator=(const Vector2D& ref);
	//벡터 * 스칼라
	Vector2D operator*(const float ref);

	bool operator==(Vector2D ref);

	bool operator!=(Vector2D ref);

	float Dot(const Vector2D& ref);

	float GetDistance(const Vector2D& ref);

	double Identity()
	{
		return sqrt(x * x + y * y);
	}
	Vector2D Nomalize();

	Vector2D SetRotate(float radian);

};