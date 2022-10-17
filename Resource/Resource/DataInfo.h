#pragma once
#include <cmath>

struct Vector2
{
	Vector2() : x(0), y(0) {}
	Vector2(const Vector2& other): x(other.x), y(other.y) {}
	Vector2(double x, double y) : x(x), y(y) {}

	double x;
	double y;

	Vector2	operator+(const Vector2& v)
	{
		Vector2	result;
		result.x = this->x + v.x;
		result.y = this->y + v.y;
		return result;
	}

	Vector2	operator+=(const Vector2& v)
	{
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	Vector2	operator-(const Vector2& v)
	{
		Vector2 result;
		result.x = this->x - v.x;
		result.y = this->y - v.y;
		return result;
	};

	Vector2	operator-=(const Vector2& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	};

	Vector2	operator-()
	{
		Vector2 result;
		result.x = -this->x;
		result.y = -this->y;
		return result;
	};

	Vector2 operator*(const float& f)
	{
		Vector2	r;
		r.x = this->x * f;
		r.y = this->y * f;
		return r;
	}
	Vector2 operator*(const double& f)
	{
		Vector2	r;
		r.x = this->x * f;
		r.y = this->y * f;
		return r;
	}

	Vector2 operator*=(const double& f)
	{
		Vector2	r;
		r.x = this->x * f;
		r.y = this->y * f;
		return r;
	}

	Vector2 operator/(const float& f)
	{
		Vector2	r;
		r.x = this->x / f;
		r.y = this->y / f;
		return r;
	}

	Vector2 operator/(const double& f)
	{
		Vector2	r;
		r.x = this->x / f;
		r.y = this->y / f;
		return r;
	}

	Vector2 operator/=(const double& f)
	{
		Vector2	r;
		r.x = this->x / f;
		r.y = this->y / f;
		return r;
	}

	bool operator==(const Vector2& f)
	{
		return (f.x == this->x) && (f.y == this->y);
	}

	bool operator!=(const Vector2& f)
	{
		return (f.x != this->x) || (f.y != this->y);
	}

	double DistanceSquared(const Vector2& other)
	{
		double dx = other.x - x;
		double dy = other.y - y;
		return dx * dx + dy * dy;
	}

	double Distance(const Vector2& other)
	{
		return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
	}

	double Identity()
	{
		return sqrt(x * x + y * y);
	}

	double Dot(const Vector2& other)
	{
		return x * other.x + y * other.y;
	}

	double CrossProduct(const Vector2& a, const Vector2& b)
	{
		return a.x * b.y - a.y * b.x;
	}

	Vector2 CrossProduct(const Vector2& a, float s)
	{
		return Vector2(s * a.y, -s * a.x);
	}

	Vector2 CrossProduct(float s, const Vector2& a)
	{
		return Vector2(-s * a.y, s * a.x);
	}

	Vector2 Unit()
	{
		Vector2 unit;

		double _length = this->Identity();

		unit = *this / _length;

		return unit;
	}

	Vector2& Normalize()
	{
		double _length = this->Identity();

		this->x /= _length;
		this->y /= _length;
		
		return *this;
	}

	Vector2 Lerp(const Vector2& B, double alpha)
	{
		if(alpha < 0) alpha = 0;
		else if(alpha > 1) alpha = 1;
		return Vector2(this->x * (1 - alpha) + B.x * alpha, this->y * (1 - alpha) + B.y * alpha);
	}
};

template<typename T>
void Swap(T& value1, T& value2)
{
	T temp = value1;
	value1 = value2;
	value2 = temp;
}

struct MyRect
{
	double cx, cy, dx, dy;
};