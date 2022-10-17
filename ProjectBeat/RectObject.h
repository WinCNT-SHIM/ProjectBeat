#pragma once
#include "GameObject.h"
class D2DEngine;

//AABB
class RectObject : public GameObject
{
public:
	RectObject(Vector2D _pos = Vector2D(0,0), Vector2D _Rc = Vector2D(0, 0));
	virtual ~RectObject();
	
};

