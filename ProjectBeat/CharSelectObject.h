#pragma once
class CharSelectObject : public GameObject
{
public:
	CharSelectObject(string _SheetName, string _SpriteName, Vector2D _pos = Vector2D(0, 0), Vector2D _rt = Vector2D(10, 10), Vector2D _Rotate = Vector2D(1, 0),
		Vector2D _Scale = Vector2D(1, 1), Vector2D _Pivot = Vector2D(0, 0), string _tag = " ");
	virtual ~CharSelectObject();
};

