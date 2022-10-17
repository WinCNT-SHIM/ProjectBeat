#include "GamePCH.h"
#include "SpriteObject.h"

//"0001_Ball_Sheet", "ARM1" 테스트용?
SpriteObject::SpriteObject(string _SheetName, string _SpriteName,float _Ratio, Vector2D _pos, Vector2D _rt, Vector2D _Rotate,
	Vector2D _Scale, Vector2D _Pivot, string _tag) :
	GameObject(_pos, _Rotate, _Scale, _Pivot, _tag)
{
	AABBCollider* _Collider = AddComponent<AABBCollider>();
	_Collider->Init(_rt);
	
	AddComponent<SpriteRenderer>()->Init(_SheetName, _SpriteName, _Ratio);
}

SpriteObject::~SpriteObject()
{

}
