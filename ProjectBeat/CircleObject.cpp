#include "GamePCH.h"
#include "CircleObject.h"

CircleObject::CircleObject(Vector2D _pos, float _Radius) : GameObject(_pos)
{
	CircleCollider* Instance = AddComponent<CircleCollider>();
	AddComponent<CircleRender>()->Init(_Radius);
	collider = Instance;
	Instance->Init(_Radius);
	m_Pyhsics = AddComponent<Physics>();
	AddComponent<CircleRender>()->Init(_Radius);
}

CircleObject::~CircleObject()
{

}

