#pragma once
#include "GameObject.h"
#include <windows.h>
class OBBObject : public GameObject
{
public:
	OBBObject(Vector2D _pos, Vector2D _rt, Vector2D _Gradient = Vector2D(1, 0), Vector2D _Scale = Vector2D(1, 1), Vector2D _Pivot = Vector2D(0,0));
	virtual ~OBBObject();

};

