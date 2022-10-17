#pragma once
class SpriteObject : public GameObject
{
public:
	SpriteObject(string _SheetName , string _SpriteName,float _Ratio = 0.2f, Vector2D _pos = Vector2D(0, 0), Vector2D _rt = Vector2D(10, 10), Vector2D _Rotate = Vector2D(1, 0),
		Vector2D _Scale = Vector2D(1, 1), Vector2D _Pivot = Vector2D(0, 0), string _tag = " ");
	virtual ~SpriteObject();
};

