#pragma once
#include "GameObject.h"

class CircleObject :public GameObject
{
public:
	CircleObject(Vector2D _pos, float _Radius);
	virtual ~CircleObject();
};

