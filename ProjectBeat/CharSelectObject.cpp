#include "GamePCH.h"
#include "CharSelectObject.h"

//"0001_Ball_Sheet", "ARM1" 테스트용?
CharSelectObject::CharSelectObject(string _SheetName, string _SpriteName, Vector2D _pos, Vector2D _rt, Vector2D _Rotate, Vector2D _Scale, Vector2D _Pivot, string _tag) : GameObject(_pos,_Rotate,_Scale,_Pivot,_tag)
{
AABBCollider* _Collider = AddComponent<AABBCollider>();
_Collider->Init(_rt);
AddComponent<SpriteRenderer>()->Init(_SheetName, _SpriteName,0.8f);
}

CharSelectObject::~CharSelectObject()
{
}
