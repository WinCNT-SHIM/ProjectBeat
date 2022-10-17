#pragma once
#include <vector>
class TESTHuman : GameObject
{
public:
	TESTHuman(Vector2D _pos = Vector2D(0, 0), Vector2D _Rotate = Vector2D(1, 0), Vector2D _Scale = Vector2D(1, 1), string _teg = "test");
	~TESTHuman();
public:
	vector<GameObject*>m_MyParts; //파츠를 저장하기 위한 벡터
private:

	void CreateParts(Vector2D _pos, Vector2D rc, Vector2D _Gradient, Vector2D _Scale, Vector2D _Pivot, int _num, string spriteName);
};