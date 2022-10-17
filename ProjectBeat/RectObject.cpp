#include "GamePCH.h"
#include "RectObject.h"

RectObject::RectObject(Vector2D _pos, Vector2D _Rc) :GameObject(_pos)
{
	AABBCollider* instance = AddComponent<AABBCollider>();
	collider = instance;
	instance->Init(_Rc);

	m_Pyhsics = AddComponent<Physics>();
	m_Pyhsics->init(ColliderType::AABB);

	AddComponent<RectRender>()->Init(-_Rc.x, -_Rc.y, _Rc.x, _Rc.y);
	SetName("RectObject");
}

RectObject::~RectObject()
{
}

